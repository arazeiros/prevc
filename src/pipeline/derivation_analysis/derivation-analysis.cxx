#include <prevc/pipeline/derivation_analysis/derivation-analysis.hxx>
#include <utility>
#include <prevc/pipeline/AST/atom.hxx>
#include <prevc/pipeline/AST/binary-operation.hxx>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/parenthesis.hxx>
#include <prevc/pipeline/AST/unary-operation.hxx>

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
                        InternalError::raise("illegal state: case not handled");
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

                    default:
                        InternalError::raise("illegal state: case not handled");
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

                        default:
                            InternalError::raise("illegal state: case not handled");
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
                        /* The following cases have to be implemented somewhere else*/
                        case T::E0:
                        case T::E1:
                        case T::E2:
                        case T::E7:
                        /* --- */

                        case T::Source:
                        case T::Expression:
                        case T::E5:
                        case T::ExtUnary:
                        case T::E6:
                        case T::E8:
                            return analyze(pipeline, nodes[0], nullptr);

                        case T::E3:
                        case T::E4:
                        {
                            auto left = (AST::Expression*) analyze(pipeline, nodes[0], nullptr);
                            return analyze(pipeline, nodes[1], left);
                        }

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

                        case syntax_analysis::VariableType::Parenthesis:
                        {
                            auto sub = (AST::Expression*) analyze(pipeline, nodes[1], nullptr);

                            return new AST::Parenthesis(
                                    pipeline,
                                    util::Location(terminal_location(0), terminal_location(2)),
                                    sub);
                        }
                    }
                }

                InternalError::raise("illegal state: case not handled");
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
