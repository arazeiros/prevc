#!/usr/bin/python3


import sys
import re


class CompileTimeError(Exception):
    pass


class Rule:
    def __init__(self, type):
        self.type = type

    def is_terminal(self):
        return self.type == 'terminal'

    def is_variable(self):
        return self.type == 'variable'


class TerminalRule(Rule):
    def __init__(self, value):
        Rule.__init__(self, 'terminal')
        self.value = value


class VariableRule(Rule):
    def __init__(self, variable):
        Rule.__init__(self, 'variable')
        self.variable = variable


class Production:
    def __init__(self, rules):
        self.rules = rules


class Variable:
    def __init__(self, line_number, name, productions):
        self.line_number = line_number
        self.name = name
        self.productions = productions
        self.terminal_prefix_productions = []
        self.touched = False
        self.accepts = {}
        self.can_be_empty = False

    def is_touched(self):
        if not self.touched:
            self.touched = True
            return False
        return True

    def untouch(self):
        self.touched = False


class GrammarParser:
    def __init__(self, file_name):
        self.file_name = file_name
        self.variables = []
        self.variables_map = {}
        try:
            self.file = open(file_name)
            try:
                self.generate()
            except CompileTimeError:
                sys.exit(1)
            self.file.close()
        except FileNotFoundError:
            self.print_error(0, 'file \'{:s}\' not found'.format(file_name))

    def print_error(self, line_number, message):
        print('ERROR: {:s}:{:d}: {:s}'.format(self.file_name, line_number, message))

    def print_warning(self, line_number, message):
        print('warning: {:s}:{:d}: {:s}'.format(self.file_name, line_number, message))

    def extract_lines(self):
        lines = [line.strip() for line in self.file.readlines()]
        lines = [(i + 1, line) for i, line in enumerate(lines) if len(line) > 0 and line[0] != '#']
        regex = r'\A[A-Z]\w*\s*->\s*(\$\s*|(([A-Z]\w*|\w+)\s*)+)(\|\s*(\$\s*|(([A-Z]\w*|\w+)\s*)+))*\Z'
        for i, line in lines:
            if not re.match(regex, line):
                self.print_error(i, 'syntax error')
                raise CompileTimeError()
        if len(lines) == 0:
            self.print_error(0, 'at least one variable have to be declared')
            raise CompileTimeError()
        return lines

    def untouch_variables(self):
        for variable in self.variables:
            variable.untouch()

    def parse_variables(self, lines):
        for i, line in lines:
            name, ext = line.split('->')
            productions = [re.split(r'\s+', p.strip()) for p in ext.split('|')]
            self.variables.append(Variable(i, name.strip(), productions))

    def map_variables(self):
        indices_to_remove = []
        for i, variable in enumerate(self.variables):
            if variable.name in self.variables_map:
                indices_to_remove.append(i)
                self.variables_map[variable.name].productions.extend(variable.productions)
            else:
                self.variables_map[variable.name] = variable
        for i in reversed(indices_to_remove):
            del self.variables[i]

    def parse_productions(self, variable):
        if variable.is_touched():
            return
        productions = []
        for production in variable.productions:
            rules = []
            for token in production:
                if token == '$':
                    variable.can_be_empty = True
                elif token[0].isupper():
                    if token not in self.variables_map:
                        message = 'variable name \'{:s}\' is not declared'. format(token)
                        self.print_error(variable.line_number, message)
                        raise CompileTimeError()
                    link_variable = self.variables_map[token]
                    self.parse_productions(link_variable)
                    rules.append(VariableRule(link_variable))
                else:
                    rules.append(TerminalRule(token))
            if len(rules) > 0:
                p = Production(rules)
                productions.append(p)
                if rules[0].is_terminal():
                    variable.terminal_prefix_productions.append(p)

        variable.productions = productions

    def check_calculated_variables(self):
        for variable in self.variables:
            if not variable.is_touched():
                message = 'variable \'{:s}\' declared, but never used'.format(variable.name)
                self.print_warning(variable.line_number, message)
                variable.untouch()
        self.variables = [variable for variable in self.variables if variable.is_touched()]
        self.untouch_variables()

    def check_left_recursion_variables(self):

        def is_left_recursive(current_variable):
            if current_variable.is_touched():
                current_variable.untouch()
                return True
            for production in current_variable.productions:
                for rule in production.rules:
                    if rule.is_terminal():
                        break
                    result = is_left_recursive(rule.variable)
                    if result:
                        current_variable.untouch()
                        return True
                    if not rule.variable.can_be_empty:
                        break

            current_variable.untouch()
            return False

        self.untouch_variables()

        for variable in self.variables:
            if is_left_recursive(variable):
                self.print_error(variable.line_number, 'variable \'{:s}\' is left recursive'.format(variable.name))
                raise CompileTimeError()

    def calculate_accepted_for_first_rules(self, variable):
        if variable.is_touched():
            return

        for production in variable.productions:
            for rule in production.rules:
                if rule.is_variable():
                    if rule.variable.can_be_empty:
                        continue
                    else:
                        break
                else:
                    if rule.value in variable.accepts:
                        self.print_error(variable.line_number, 'grammar is not LL(1)')
                        raise CompileTimeError()
                    variable.accepts[rule.value] = True
                    break

        for production in variable.productions:
            for rule in production.rules:
                if rule.is_terminal():
                    break
                self.calculate_accepted_for_first_rules(rule.variable)
                for terminal in rule.variable.accepts:
                    if terminal in variable.accepts:
                        self.print_error(variable.line_number, 'grammar is not LL(1)')
                        raise CompileTimeError()
                    variable.accepts[terminal] = True
                if not rule.variable.can_be_empty:
                    break

    def calculate_accepted(self):
        self.untouch_variables()
        for variable in self.variables:
            self.calculate_accepted_for_first_rules(variable)

    def generate(self):
        lines = self.extract_lines()
        self.parse_variables(lines)
        self.map_variables()
        self.parse_productions(self.variables[0])
        self.check_calculated_variables()
        self.check_left_recursion_variables()
        self.calculate_accepted()
        self.untouch_variables()


class SourceGenerator:

    def __init__(self, file_name):
        self.indentation = 0
        self.file = open(file_name, 'w')

    def indent(self):
        self.indentation += 1

    def unindent(self):
        self.indentation -= 1

    def line(self, code):
        indentation_spaces = ' ' * (self.indentation * 4)
        self.file.write('{:s}{:s}\n'.format(indentation_spaces, code))

    def scope_in(self):
        self.line('{')
        self.indent()

    def scope_out(self):
        self.unindent()
        self.line('}')

    def empty_line(self):
        self.line('')

    def include(self, header):
        self.line('#include <{:s}>'.format(header))

    def define(self, name):
        self.line('#define {:s}'.format(name))

    def ifndef(self, name):
        self.line('#ifndef {:s}'.format(name))

    def endif(self):
        self.line('#endif')

    def namespace(self, name):
        self.line('namespace {:s}'.format(name))

    def close(self):
        self.file.close()


class VariableHeaderGenerator(SourceGenerator):

    def __init__(self, file_name, root_variable):
        SourceGenerator.__init__(self, file_name)
        self.root_variable = root_variable
        self.last_id = 0
        self.variables = []
        self.generate()
        self.close()

    def generate_variable(self, variable):
        if variable.is_touched():
            return
        for production in variable.productions:
            for rule in production.rules:
                if rule.is_variable():
                    self.generate_variable(rule.variable)

        self.last_id += 1
        self.line('{:s} = {:d},'.format(variable.name, self.last_id))
        self.variables.append(variable)

    def generate_enum(self):
        self.line('enum class VariableType')
        self.scope_in()
        self.generate_variable(self.root_variable)
        self.line('_ROOT = {:d}'.format(self.last_id))
        self.unindent()
        self.line('};')
        self.empty_line()

    def generate_to_string(self):
        self.line('constexpr static const char* to_string(VariableType type)')
        self.scope_in()
        self.line('switch (type)')
        self.scope_in()

        for variable in self.variables:
            self.line('case VariableType::{:s}: return "{:s}";'.format(variable.name, variable.name))

        self.scope_out()
        self.scope_out()

    def generate(self):
        protection = 'PREVC_PIPELINE_SYNTAXANALYSIS_VARIABLETYPE_HXX'
        self.empty_line()
        self.ifndef(protection)
        self.define(protection)
        self.empty_line()
        self.namespace('prevc')
        self.scope_in()
        self.namespace('pipeline')
        self.scope_in()
        self.namespace('syntax_analysis')
        self.scope_in()
        self.generate_enum()
        self.generate_to_string()
        self.scope_out()
        self.scope_out()
        self.scope_out()
        self.empty_line()
        self.endif()
        self.empty_line()


class BuilderHeaderGenerator(SourceGenerator):

    def __init__(self, file_name, root_variable):
        SourceGenerator.__init__(self, file_name)
        self.root_variable = root_variable
        self.generate()
        self.close()

    def generate_headers(self):
        self.include('prevc/pipeline/pipeline.hxx')
        self.include('prevc/pipeline/syntax_analysis/syntax-node.hxx')

    def generate_constructor(self):
        self.line('SyntaxTreeBuilder(Pipeline* pipeline) noexcept;')

    def generate_build(self):
        self.line('SyntaxNode* build();')

    def generate_public(self):
        self.generate_constructor()
        self.generate_build()

    def generate_attributes(self):
        self.line('Pipeline* pipeline;')
        self.line('lexical_analysis::SymbolsVector::const_iterator symbol;')

    def generate_consume(self):
        self.line('SyntaxTerminal* consume() noexcept;')

    def generate_require(self):
        self.line('SyntaxTerminal* require(const lexical_analysis::Token& token);')

    def generate_variable(self, variable):

        if variable.is_touched():
            return

        for production in variable.productions:
            for rule in production.rules:
                if rule.is_variable():
                    self.generate_variable(rule.variable)

        self.line('SyntaxVariable* parse{:s}();'.format(variable.name))

    def generate_private(self):
        self.generate_attributes()
        self.empty_line()
        self.generate_consume()
        self.generate_require()
        self.empty_line()
        self.generate_variable(self.root_variable)

    def generate_class(self):
        self.line('class SyntaxTreeBuilder')
        self.line('{')
        self.line('public:')
        self.indent()
        self.generate_public()
        self.unindent()
        self.empty_line()
        self.line('private:')
        self.indent()
        self.generate_private()
        self.unindent()
        self.line('};')

    def generate(self):
        protection = 'PREVC_PIPELINE_SYNTAXANALYSIS_SYNTAXTREEBUILDER_HXX'
        self.empty_line()
        self.ifndef(protection)
        self.define(protection)
        self.empty_line()
        self.generate_headers()
        self.empty_line()
        self.namespace('prevc')
        self.scope_in()
        self.namespace('pipeline')
        self.scope_in()
        self.namespace('syntax_analysis')
        self.scope_in()
        self.generate_class()
        self.scope_out()
        self.scope_out()
        self.scope_out()
        self.empty_line()
        self.endif()
        self.empty_line()


class BuilderSourceGenerator(SourceGenerator):

    def __init__(self, file_name, root_variable):
        SourceGenerator.__init__(self, file_name)
        self.root_variable = root_variable
        self.generate()
        self.close()

    def generate_headers(self):
        self.include('prevc/pipeline/syntax_analysis/derivation-tree-generator.hxx')
        self.include('prevc/error.hxx')
        self.include('prevc/pipeline/syntax_analysis/syntax-node.hxx')

    def generate_constructor(self):
        self.line('SyntaxTreeBuilder::SyntaxTreeBuilder(Pipeline* pipeline) noexcept:')
        self.indent()
        self.line('pipeline(pipeline)')
        self.unindent()
        self.scope_in()
        self.line('symbol = pipeline->symbols_vector.begin();')
        self.scope_out()
        self.empty_line()

    def generate_build(self):
        self.line('SyntaxNode* SyntaxTreeBuilder::build()')
        self.scope_in()
        self.line('return parse{:s}();'.format(self.root_variable.name))
        self.scope_out()
        self.empty_line()

    def generate_consume(self):
        self.line('SyntaxTerminal* SyntaxTreeBuilder::consume() noexcept')
        self.scope_in()
        self.line('SyntaxTerminal* terminal = new SyntaxTerminal(*symbol);')
        self.line('++symbol;')
        self.line('return terminal;')
        self.scope_out()
        self.empty_line()

    def generate_require(self):
        self.line('SyntaxTerminal* SyntaxTreeBuilder::require(const lexical_analysis::Token& token)')
        self.scope_in()
        self.line('if (symbol->token != token)')
        self.scope_in()
        self.line('CompileTimeError::raise(pipeline->file_name.c_str(), symbol->location, util::String::format(')
        self.indent()
        self.line('"expected token %s, but found %s", lexical_analysis::to_string(token), ')
        self.line('lexical_analysis::to_string(symbol->token)));')
        self.unindent()
        self.scope_out()
        self.empty_line()
        self.line('return consume();')
        self.scope_out()
        self.empty_line()

    def generate_variable(self, variable):
        if variable.is_touched():
            return
        for production in variable.productions:
            for rule in production.rules:
                if rule.is_variable():
                    self.generate_variable(rule.variable)

        self.line('SyntaxVariable* SyntaxTreeBuilder::parse{:s}()'.format(variable.name))
        self.scope_in()
        self.line('std::vector<const SyntaxNode*> nodes;')
        self.empty_line()
        self.line('switch (symbol->token)')
        self.scope_in()

        for production in variable.productions:
            if len(production.rules) == 0:  # the production is "empty" (epsilon, $)
                continue
            first_rule = production.rules[0]
            if first_rule.is_terminal():
                self.line('case lexical_analysis::Token::{:s}:'.format(first_rule.value.upper()))
                self.scope_in()
                self.line('nodes.emplace_back(consume());')
            else:
                for rule in production.rules:
                    if rule.is_terminal():
                        self.line('case lexical_analysis::Token::{:s}:'.format(rule.value.upper()))
                        break
                    for key in rule.variable.accepts:
                        self.line('case lexical_analysis::Token::{:s}:'.format(key.upper()))
                    if not rule.variable.can_be_empty:
                        break
                self.scope_in()
                self.line('nodes.emplace_back(parse{:s}());'.format(first_rule.variable.name))
            for i in range(1, len(production.rules)):
                rule = production.rules[i]
                if rule.is_terminal():
                    self.line('nodes.emplace_back(require(lexical_analysis::Token::{:s}));'.format(rule.value.upper()))
                else:
                    self.line('nodes.emplace_back(parse{:s}());'.format(rule.variable.name))

            self.line('break;')
            self.scope_out()
            self.empty_line()

        self.line('default:')
        self.scope_in()

        if variable.can_be_empty:
            self.line('break;')
        else:
            self.line('CompileTimeError::raise(pipeline->file_name.c_str(), symbol->location, util::String::format(')
            self.indent()
            placeholders = ''
            replacements = ''
            for key in variable.accepts:
                placeholders += '%s, '
                replacements += 'lexical_analysis::to_string(lexical_analysis::Token::{:s}), '.format(key.upper())
            placeholders = placeholders[:-2]
            replacements = replacements[:-2]
            self.line('"expected one token between: {:s}; but found %s", {:s}, '.format(placeholders, replacements))
            self.line('lexical_analysis::to_string(symbol->token)));')
            self.unindent()

        self.scope_out()
        self.scope_out()
        self.empty_line()
        self.line('return new SyntaxVariable(VariableType::{:s}, std::move(nodes));'.format(variable.name))
        self.scope_out()
        self.empty_line()

    def generate_methods(self):
        self.generate_constructor()
        self.generate_build()
        self.generate_consume()
        self.generate_require()
        self.generate_variable(self.root_variable)

    def generate(self):
        self.generate_headers()
        self.empty_line()
        self.namespace('prevc')
        self.scope_in()
        self.namespace('pipeline')
        self.scope_in()
        self.namespace('syntax_analysis')
        self.scope_in()
        self.generate_methods()
        self.scope_out()
        self.scope_out()
        self.scope_out()
        self.empty_line()


def main():
    grammar_file = None
    variable_header_file = None
    builder_header_file = None
    builder_source_file = None
    expecting = 'grammar'

    for i in range(1, len(sys.argv)):
        s = sys.argv[i]

        if expecting == 'variable header':
            variable_header_file = s
            expecting = 'grammar'
        elif expecting == 'builder header':
            builder_header_file = s
            expecting = 'grammar'
        elif expecting == 'builder source':
            builder_source_file = s
            expecting = 'grammar'
        else:
            if s == '-vh':
                expecting = 'variable header'
            elif s == '-bh':
                expecting = 'builder header'
            elif s == '-bs':
                expecting = 'builder source'
            else:
                grammar_file = s

    if expecting != 'grammar':
        print('error: excepting argument for the option as command line argument, but nothing found')
        sys.exit(1)

    parser = GrammarParser(grammar_file)
    root_variable = parser.variables[0]

    parser.untouch_variables()
    VariableHeaderGenerator(variable_header_file, root_variable)

    parser.untouch_variables()
    BuilderHeaderGenerator(builder_header_file, root_variable)

    parser.untouch_variables()
    BuilderSourceGenerator(builder_source_file, root_variable)


if __name__ == "__main__":
    main()
