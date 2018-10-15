#include <prevc/pipeline/AST/parenthesis.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Parenthesis::Parenthesis(Pipeline* pipeline, util::Location&& location, Expression* sub_expression):
                Expression(pipeline, std::move(location)),
                sub_expression(sub_expression)
            {

            }

            Parenthesis::~Parenthesis()
            {
                delete sub_expression;
            }

            llvm::Value* Parenthesis::generate_IR(llvm::IRBuilder<>* builder)
            {
                return sub_expression->generate_IR(builder);
            }

            std::optional<int64_t> Parenthesis::evaluate_as_integer() const noexcept
            {
                return sub_expression->evaluate_as_integer();
            }

            util::String Parenthesis::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "parenthesis", "location": %s, "sub": %s})",
                        location.to_string().c_str(),
                        sub_expression->to_string().c_str());
            }
        }
    }
}
