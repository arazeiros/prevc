#include <prevc/pipeline/AST/unary-operation.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            UnaryOperation::UnaryOperation(Pipeline* pipeline, util::Location&& location, UnaryOperation::Operator operator_, Expression* sub_expression):
                Expression(pipeline, std::move(location)),
                operator_(operator_),
                sub_expression(sub_expression)
            {

            }

            UnaryOperation::~UnaryOperation()
            {
                delete sub_expression;
            }

            llvm::Value* UnaryOperation::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto sub = sub_expression->generate_IR(builder);

                switch (operator_)
                {
                    case Operator::PLUS:
                        return sub;

                    case Operator::MINUS:
                        return builder->CreateNeg(sub);

                    case Operator::NOT:
                        return builder->CreateXor(sub, 1);
                }

                InternalError::raise("illegal state: case not handled");
                return nullptr;
            }

            util::String UnaryOperation::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "unary-operation", "location": %s, "operator": "%s", "sub": %s})",
                        location.to_string().c_str(),
                        AST::to_string(operator_),
                        sub_expression->to_string().c_str());
            }
        }
    }
}
