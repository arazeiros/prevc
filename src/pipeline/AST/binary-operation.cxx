#include <prevc/pipeline/AST/binary-operation.hxx>
#include <utility>

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

                InternalError::raise("illegal state: case not handled");
                return nullptr;
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
