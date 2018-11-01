#include <prevc/pipeline/AST/binary-operation.hxx>
#include <utility>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            BinaryOperation::BinaryOperation(Pipeline* pipeline, util::Location&& location,
                    BinaryOperation::Operator operator_, Expression* left_expression, Expression* right_expression):
                Expression(pipeline, std::move(location)),
                operator_(operator_),
                left_expression(left_expression),
                right_expression(right_expression)
            {

            }

            BinaryOperation::~BinaryOperation()
            {
                delete left_expression;
                delete right_expression;
            }

            void BinaryOperation::check_semantics()
            {
                left_expression->check_semantics();
                right_expression->check_semantics();

                // TODO check that expressions are of the same type
                // TODO check that operator can be used with those expressions types
            }

            llvm::Value* BinaryOperation::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto left  = left_expression->generate_IR(builder);
                auto right = right_expression->generate_IR(builder);

                switch (operator_)
                {
                    case Operator::OR:
                        return builder->CreateOr(left, right);

                    case Operator::XOR:
                        return builder->CreateXor(left, right);

                    case Operator::AND:
                        return builder->CreateAnd(left, right);

                    case Operator::EQU:
                        return builder->CreateICmpEQ(left, right);

                    case Operator::NEQ:
                        return builder->CreateICmpNE(left, right);

                    case Operator::LTH:
                        return builder->CreateICmpSLT(left, right);

                    case Operator::LEQ:
                        return builder->CreateICmpSLE(left, right);

                    case Operator::GTH:
                        return builder->CreateICmpSGT(left, right);

                    case Operator::GEQ:
                        return builder->CreateICmpSGE(left, right);

                    case Operator::ADD:
                        return builder->CreateAdd(left, right);

                    case Operator::SUBTRACT:
                        return builder->CreateSub(left, right);

                    case Operator::MULTIPLY:
                        return builder->CreateMul(left, right);

                    case Operator::DIVIDE:
                        return builder->CreateSDiv(left, right);

                    case Operator::MODULE:
                        return builder->CreateSRem(left, right);
                }
            }

            std::optional<int64_t> BinaryOperation::evaluate_as_integer() const noexcept
            {
                auto optional_right = right_expression->evaluate_as_integer();
                auto optional_left  = left_expression->evaluate_as_integer();

                if (!optional_right.has_value() || !optional_left.has_value())
                    return {};

                auto right = optional_right.value();
                auto left  = optional_left.value();

                switch (operator_)
                {
                    case Operator::ADD:
                        return left + right;

                    case Operator::SUBTRACT:
                        return left - right;

                    case Operator::MULTIPLY:
                        return left * right;

                    case Operator::DIVIDE:
                    {
                        if (right == 0)
                            return {};

                        return left / right;
                    }

                    case Operator::MODULE:
                    {
                        if (right == 0)
                            return {};

                        return left % right;
                    }

                    default:
                        return {};
                }
            }

            const semantic_analysis::Type* BinaryOperation::get_semantic_type()
            {
                using SAtom = semantic_analysis::AtomType;

                switch (operator_)
                {
                    case Operator::EQU:
                    case Operator::NEQ:
                    case Operator::LTH:
                    case Operator::LEQ:
                    case Operator::GTH:
                    case Operator::GEQ:
                        return pipeline->type_system->get_or_insert("bool", [] () { return new SAtom(SAtom::Kind::BOOL); });

                    case Operator::OR:
                    case Operator::XOR:
                    case Operator::AND:
                    case Operator::ADD:
                    case Operator::SUBTRACT:
                    case Operator::MULTIPLY:
                    case Operator::DIVIDE:
                    case Operator::MODULE:
                        // This is true only if both operators must be of the same type as language rule.
                        return left_expression->get_semantic_type();
                }
            }

            util::String BinaryOperation::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "binary-operation", "location": %s, "operator": "%s", "left": %s, "right": %s})",
                        location.to_string().c_str(),
                        AST::to_string(operator_),
                        left_expression->to_string().c_str(),
                        right_expression->to_string().c_str());
            }
        }
    }
}
