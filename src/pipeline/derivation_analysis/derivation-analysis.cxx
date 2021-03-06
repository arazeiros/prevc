#include <prevc/pipeline/derivation_analysis/derivation-analysis.hxx>
#include <utility>
#include <prevc/pipeline/AST/arguments.hxx>
#include <prevc/pipeline/AST/array-access.hxx>
#include <prevc/pipeline/AST/array-type.hxx>
#include <prevc/pipeline/AST/assignment.hxx>
#include <prevc/pipeline/AST/atom.hxx>
#include <prevc/pipeline/AST/binary-operation.hxx>
#include <prevc/pipeline/AST/cast.hxx>
#include <prevc/pipeline/AST/component.hxx>
#include <prevc/pipeline/AST/component-access.hxx>
#include <prevc/pipeline/AST/components.hxx>
#include <prevc/pipeline/AST/compound.hxx>
#include <prevc/pipeline/AST/declarations.hxx>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/expression-statement.hxx>
#include <prevc/pipeline/AST/function-call.hxx>
#include <prevc/pipeline/AST/function-declaration.hxx>
#include <prevc/pipeline/AST/if.hxx>
#include <prevc/pipeline/AST/parameters.hxx>
#include <prevc/pipeline/AST/parenthesis.hxx>
#include <prevc/pipeline/AST/record-type.hxx>
#include <prevc/pipeline/AST/statements.hxx>
#include <prevc/pipeline/AST/unary-operation.hxx>
#include <prevc/pipeline/AST/type.hxx>
#include <prevc/pipeline/AST/named-type.hxx>
#include <prevc/pipeline/AST/new.hxx>
#include <prevc/pipeline/AST/pointer-type.hxx>
#include <prevc/pipeline/AST/primitive-type.hxx>
#include <prevc/pipeline/AST/type-declaration.hxx>
#include <prevc/pipeline/AST/variable-declaration.hxx>
#include <prevc/pipeline/AST/variable-name.hxx>
#include <prevc/pipeline/AST/while.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace derivation_analysis
        {
            using Terminal = const syntax_analysis::SyntaxTerminal*;
            using Variable = const syntax_analysis::SyntaxVariable*;

            DerivationAnalysis::DerivationAnalysis(Pipeline *pipeline):
                Phase(pipeline)
            {

            }

            DerivationAnalysis::~DerivationAnalysis() = default;

            static AST::BinaryOperation::Operator analyze_binary_operator(const lexical_analysis::Symbol& symbol)
            {
                switch (symbol.token)
                {
                    case lexical_analysis::Token::OR:
                        return AST::BinaryOperation::Operator::OR;

                    case lexical_analysis::Token::XOR:
                        return AST::BinaryOperation::Operator::XOR;

                    case lexical_analysis::Token::AND:
                        return AST::BinaryOperation::Operator::AND;

                    case lexical_analysis::Token::EQU:
                        return AST::BinaryOperation::Operator::EQU;

                    case lexical_analysis::Token::NEQ:
                        return AST::BinaryOperation::Operator::NEQ;

                    case lexical_analysis::Token::LTH:
                        return AST::BinaryOperation::Operator::LTH;

                    case lexical_analysis::Token::LEQ:
                        return AST::BinaryOperation::Operator::LEQ;

                    case lexical_analysis::Token::GTH:
                        return AST::BinaryOperation::Operator::GTH;

                    case lexical_analysis::Token::GEQ:
                        return AST::BinaryOperation::Operator::GEQ;

                    case lexical_analysis::Token::ADD:
                        return AST::BinaryOperation::Operator::ADD;

                    case lexical_analysis::Token::SUB:
                        return AST::BinaryOperation::Operator::SUBTRACT;

                    case lexical_analysis::Token::MUL:
                        return AST::BinaryOperation::Operator::MULTIPLY;

                    case lexical_analysis::Token::DIV:
                        return AST::BinaryOperation::Operator::DIVIDE;

                    case lexical_analysis::Token::MOD:
                        return AST::BinaryOperation::Operator::MODULE;

                    default:
                        InternalError::raise("derivation analysis: illegal state: case not handled");
                        return AST::BinaryOperation::Operator::MODULE; // never reached, disable warnings
                }
            }

            static AST::UnaryOperation::Operator analyze_unary_operator(const lexical_analysis::Symbol& symbol)
            {
                switch (symbol.token)
                {
                    case lexical_analysis::Token::ADD:
                        return AST::UnaryOperation::Operator::PLUS;

                    case lexical_analysis::Token::SUB:
                        return AST::UnaryOperation::Operator::MINUS;

                    case lexical_analysis::Token::NOT:
                        return AST::UnaryOperation::Operator::NOT;

                    case lexical_analysis::Token::DEL:
                        return AST::UnaryOperation::Operator::DEL;

                    case lexical_analysis::Token::MEM:
                        return AST::UnaryOperation::Operator::MEM;

                    case lexical_analysis::Token::VAL:
                        return AST::UnaryOperation::Operator::VAL;

                    default:
                        InternalError::raise(util::String::format(
                                "derivation analysis: illegal state: case not handled: terminal syntax node: %s",
                                to_string(symbol.token)));
                        return AST::UnaryOperation::Operator::NOT; // never reached, disable warnings
                }
            }

            static AST::Node* analyze(Pipeline* pipeline, const syntax_analysis::SyntaxNode* syntax_node, AST::Node* accumulator);

            template <typename E, int I0, int I1>
            static void collect_extension(Pipeline* pipeline, std::vector<E>* vector, const syntax_analysis::SyntaxNode* node)
            {
                auto variable = (Variable) node;

                if (variable->nodes.empty())
                    return;

                vector->emplace_back((E) analyze(pipeline, variable->nodes[I0], nullptr));
                collect_extension<E, I0, I1>(pipeline, vector, variable->nodes[I1]);
            }

            template <typename E, int I0, int I1, typename C>
            static C* collect_nodes(Pipeline* pipeline, const std::vector<const syntax_analysis::SyntaxNode*>& nodes)
            {
                std::vector<E> collection;
                auto first = (E) analyze(pipeline, nodes[0], nullptr);
                collection.emplace_back(first);
                collect_extension<E, I0, I1>(pipeline, &collection, nodes[1]);
                util::Location location(collection.front()->location, collection.back()->location);
                return new C(pipeline, std::move(location), std::move(collection));
            }

            static AST::Node* analyze(Pipeline* pipeline, const syntax_analysis::SyntaxNode* syntax_node, AST::Node* accumulator)
            {
                using T = syntax_analysis::VariableType;

                if (syntax_node->is_terminal())
                {
                    auto terminal = (Terminal) syntax_node;
                    auto symbol = terminal->symbol;

                    switch (symbol.token)
                    {
                        case lexical_analysis::Token::INT_LITERAL:
                        {
                            return new AST::Atom(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::Atom::Type::INTEGER, symbol.lexeme);
                        }

                        case lexical_analysis::Token::CHAR_LITERAL:
                        {
                            return new AST::Atom(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::Atom::Type::CHARACTER, symbol.lexeme);
                        }

                        case lexical_analysis::Token::BOOL_LITERAL:
                        {
                            return new AST::Atom(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::Atom::Type::BOOLEAN, symbol.lexeme);
                        }

                        case lexical_analysis::Token::VOID_LITERAL:
                        {
                            return new AST::Atom(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::Atom::Type::VOID, symbol.lexeme);
                        }

                        case lexical_analysis::Token::PTR_LITERAL:
                        {
                            return new AST::Atom(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::Atom::Type::POINTER, symbol.lexeme);
                        }

                        case lexical_analysis::Token::INT:
                        {
                            return new AST::PrimitiveType(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::PrimitiveType::Name::INT);
                        }

                        case lexical_analysis::Token::CHAR:
                        {
                            return new AST::PrimitiveType(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::PrimitiveType::Name::CHAR);
                        }

                        case lexical_analysis::Token::BOOL:
                        {
                            return new AST::PrimitiveType(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::PrimitiveType::Name::BOOL);
                        }

                        case lexical_analysis::Token::VOID:
                        {
                            return new AST::PrimitiveType(
                                    pipeline,
                                    util::Location(symbol.location),
                                    AST::PrimitiveType::Name::VOID);
                        }

                        default:
                            InternalError::raise(util::String::format(
                                    "derivation analysis: illegal state: case not handled: terminal syntax node: %s",
                                    to_string(symbol.token)));
                    }
                }
                else
                {
                    auto variable = (Variable) syntax_node;
                    auto& nodes = variable->nodes;

                    const auto terminal_location = [nodes] (int index)
                    {
                        return ((Terminal) nodes[index])->symbol.location;
                    };

                    switch (variable->type)
                    {
                        case T::Source:
                        case T::Expression:
                        case T::E5:
                        case T::ExtUnary:
                        case T::E6:
                        case T::E8:
                        case T::Statement:
                        case T::Declaration:
                        case T::Type:
                            return analyze(pipeline, nodes[0], nullptr);

                        case T::E0:
                        case T::E1:
                        case T::E2:
                        case T::E3:
                        case T::E4:
                        {
                            auto left = (AST::Expression*) analyze(pipeline, nodes[0], nullptr);
                            return analyze(pipeline, nodes[1], left);
                        }

                        case T::ExtOrXor:
                        case T::ExtAnd:
                        case T::OptRel:
                        case T::ExtAddSub:
                        case T::ExtMulDivMod:
                        {
                            if (nodes.empty())
                                return accumulator;

                            auto right = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);

                            auto expression = new AST::BinaryOperation(
                                    pipeline,
                                    util::Location(accumulator->location, right->location),
                                    analyze_binary_operator(((Terminal) nodes[0])->symbol),
                                    (AST::Expression*) accumulator,
                                    right);

                            if (variable->type == T::OptRel)
                                return expression;

                            return analyze(pipeline, nodes[2], expression);
                        }

                        case T::Unary0:
                        {
                            auto sub = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);
                            auto sign = (Terminal) nodes[0];

                            return new AST::UnaryOperation(
                                    pipeline,
                                    util::Location(sign->symbol.location, sub->location),
                                    analyze_unary_operator(sign->symbol),
                                    sub);
                        }

                        case T::Unary1:
                        {
                            auto type = (AST::Type*) analyze(pipeline, nodes[1], nullptr);
                            auto sub = (AST::Expression*) analyze(pipeline, nodes[3], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, sub->location);
                            return new AST::Cast(pipeline, std::move(location), type, sub);
                        }

                        case T::New:
                        {
                            auto type = (AST::Type*) analyze(pipeline, nodes[1], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, type->location);
                            return new AST::New(pipeline, std::move(location), type);
                        }

                        case T::E7:
                        {
                            auto base = analyze(pipeline, nodes[0], nullptr);
                            return analyze(pipeline, nodes[1], base);
                        }

                        case T::ExtAccess:
                        {
                            if (nodes.empty())
                                return accumulator;

                            auto access = analyze(pipeline, nodes[0], accumulator);
                            return analyze(pipeline, nodes[1], access);
                        }

                        case T::ArrayAccess:
                        {
                            auto array = (AST::Expression*) accumulator;
                            auto index = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);
                            util::Location location(array->location, ((Terminal) nodes[2])->symbol.location);
                            return new AST::ArrayAccess(pipeline, std::move(location), array, index);
                        }

                        case T::ComponentAccess:
                        {
                            auto& symbol = ((Terminal) nodes[1])->symbol;
                            auto  record = (AST::Expression*) accumulator;
                            util::Location location(record->location, symbol.location);
                            return new AST::ComponentAccess(pipeline, std::move(location), record, symbol.lexeme);
                        }

                        case T::IdOrCall:
                        {
                            auto& symbol = ((Terminal) nodes[0])->symbol;
                            util::Location location(symbol.location);
                            auto variableName = new AST::VariableName(pipeline, std::move(location), symbol.lexeme);
                            return analyze(pipeline, nodes[1], variableName);
                        }

                        case T::Parenthesis:
                        {
                            auto sub = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);

                            return new AST::Parenthesis(
                                    pipeline,
                                    util::Location(terminal_location(0), terminal_location(2)),
                                    sub);
                        }

                        case T::OptFunctionCall:
                        {
                            if (nodes.empty())
                                return accumulator;

                            auto& name = ((AST::VariableName*) accumulator)->name;
                            auto args = (AST::Arguments*) analyze(pipeline, nodes[1], nullptr);
                            util::Location location(accumulator->location, ((Terminal) nodes[2])->symbol.location);
                            auto functionCall = new AST::FunctionCall(pipeline, std::move(location), name, args);
                            delete accumulator;
                            return functionCall;
                        }

                        case T::OptArguments:
                        {
                            if (nodes.empty())
                                return new AST::Arguments(pipeline, util::Location(0, 0), {});

                            return collect_nodes<AST::Expression*, 1, 2, AST::Arguments>(pipeline, nodes);
                        }

                        case T::Compound:
                        {
                            auto statements = (AST::Statements*) analyze(pipeline, nodes[1], nullptr);
                            auto expression = (AST::Expression*) analyze(pipeline, nodes[3], nullptr);
                            auto declarations = (AST::Declarations*) analyze(pipeline, nodes[4], nullptr);

                            const util::Location end(declarations->empty() ? expression->location : declarations->location);
                            util::Location location(statements->location, end);

                            return new AST::Compound(pipeline, std::move(location), statements, expression, declarations);
                        }

                        case T::OptWhere:
                        {
                            if (nodes.empty())
                                return new AST::Declarations(pipeline, util::Location(0, 0), {});

                            return analyze(pipeline, nodes[1], nullptr);
                        }

                        case T::Array:
                        {
                            auto size_expression = (AST::Expression*) analyze(pipeline, nodes[2], nullptr);
                            auto type = (AST::Type*) analyze(pipeline, nodes[4], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, type->location);
                            return new AST::ArrayType(pipeline, std::move(location), size_expression, type);
                        }

                        case T::Record:
                        {
                            auto components = (AST::Components*) analyze(pipeline, nodes[2], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, ((Terminal) nodes[3])->symbol.location);
                            return new AST::RecordType(pipeline, std::move(location), components);
                        }

                        case T::Pointer:
                        {
                            auto type = (AST::Type*) analyze(pipeline, nodes[1], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, type->location);
                            return new AST::PointerType(pipeline, std::move(location), type);
                        }

                        case T::NamedType:
                        {
                            auto& symbol = ((Terminal) nodes[0])->symbol;
                            return new AST::NamedType(pipeline, util::Location(symbol.location), symbol.lexeme);
                        }

                        case T::Components:
                            return collect_nodes<AST::Component*, 1, 2, AST::Components>(pipeline, nodes);

                        case T::Component:
                        {
                            auto& symbol = ((Terminal) nodes[0])->symbol;
                            auto& name = symbol.lexeme;
                            auto type = (AST::Type*) analyze(pipeline, nodes[2], nullptr);
                            util::Location location(symbol.location, type->location);
                            return new AST::Component(pipeline, std::move(location), name, type);
                        }

                        case T::Statements:
                            return collect_nodes<AST::Statement*, 1, 2, AST::Statements>(pipeline, nodes);

                        case T::ExpressionStatement:
                        {
                            auto expression = analyze(pipeline, nodes[0], nullptr);
                            return analyze(pipeline, nodes[1], expression);
                        }

                        case T::If:
                        {
                            auto  condition = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);
                            auto  then_body = (AST::Statements*) analyze(pipeline, nodes[3], nullptr);
                            auto& else_node = ((Variable) nodes[4])->nodes;

                            auto else_body = else_node.empty()
                                    ? nullptr
                                    : (AST::Statements*) analyze(pipeline, else_node[1], nullptr);

                            util::Location location(((Terminal) nodes[0])->symbol.location, ((Terminal) nodes[5])->symbol.location);
                            return new AST::If(pipeline, std::move(location), condition, then_body, else_body);
                        }

                        case T::While:
                        {
                            auto condition = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);
                            auto body = (AST::Statements*) analyze(pipeline, nodes[3], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, ((Terminal) nodes[4])->symbol.location);
                            return new AST::While(pipeline, std::move(location), condition, body);
                        }

                        case T::OptAssign:
                        {
                            auto expression = (AST::Expression*) accumulator;

                            if (nodes.empty())
                                return new AST::ExpressionStatement(pipeline, util::Location(expression->location), expression);

                            auto destination = expression;
                            auto source = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);
                            util::Location location(destination->location, source->location);
                            return new AST::Assignment(pipeline, std::move(location), destination, source);
                        }

                        case T::Declarations:
                            return collect_nodes<AST::Declaration*, 1, 2, AST::Declarations>(pipeline, nodes);

                        case T::TypeDeclaration:
                        {
                            auto& symbol = ((Terminal) nodes[1])->symbol;
                            auto& name = symbol.lexeme;
                            auto type = (AST::Type*) analyze(pipeline, nodes[3], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, type->location);
                            return new AST::TypeDeclaration(pipeline, std::move(location), name, type);
                        }

                        case T::VariableDeclaration:
                        {
                            auto& symbol = ((Terminal) nodes[1])->symbol;
                            auto& name = symbol.lexeme;
                            auto type = (AST::Type*) analyze(pipeline, nodes[3], nullptr);
                            util::Location location(((Terminal) nodes[0])->symbol.location, type->location);
                            return new AST::VariableDeclaration(pipeline, std::move(location), name, type);
                        }

                        case T::FunctionDeclaration:
                        {
                            auto& symbol              = ((Terminal) nodes[1])->symbol;
                            auto& name                = symbol.lexeme;
                            auto  parameters          = (AST::Parameters*) analyze(pipeline, nodes[3], nullptr);
                            auto  type                = (AST::Type*) analyze(pipeline, nodes[6], nullptr);
                            auto& implementation_node = ((Variable) nodes[7])->nodes;

                            auto implementation = implementation_node.empty()
                                    ? nullptr
                                    : (AST::Expression*) analyze(pipeline, implementation_node[1], nullptr);

                            util::Location location(((Terminal) nodes[0])->symbol.location,
                                    implementation == nullptr
                                        ? type->location
                                        : implementation->location);

                            return new AST::FunctionDeclaration(pipeline, std::move(location), name, type,
                                                                parameters, implementation);
                        }

                        case T::OptParameters:
                        {
                            if (nodes.empty())
                                return new AST::Parameters(pipeline, util::Location(0, 0), {});

                            return collect_nodes<AST::Parameter*, 1, 2, AST::Parameters>(pipeline, nodes);
                        }

                        case T::Parameter:
                        {
                            auto& symbol = ((Terminal) nodes[0])->symbol;
                            auto& name = symbol.lexeme;
                            auto type = (AST::Type*) analyze(pipeline, nodes[2], nullptr);
                            util::Location location(symbol.location, type->location);
                            return new AST::Parameter(pipeline, std::move(location), name, type);
                        }

                        default:
                            break; // disable warnings
                    }

                    InternalError::raise(util::String::format(
                            "derivation analysis: illegal state: case not handled: variable syntax node: %s",
                            variable->to_string().c_str()));
                }

                InternalError::raise("derivation analysis: illegal state");
                return nullptr; // should never come here, but disable warnings
            }

            void DerivationAnalysis::complete_0()
            {
                pipeline->abstract_syntax_tree = analyze(pipeline, pipeline->derivation_tree, nullptr);
                pipeline->release_derivation_tree();
                pipeline->release_symbols_vector();
            }
        }
    }
}
