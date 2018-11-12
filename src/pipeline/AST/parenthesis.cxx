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

            void Parenthesis::check_semantics()
            {
                sub_expression->check_semantics();
            }

            llvm::Value* Parenthesis::generate_IR(llvm::IRBuilder<>* builder)
            {
                return sub_expression->generate_IR(builder);
            }

            std::optional<int64_t> Parenthesis::evaluate_as_integer() const noexcept
            {
                return sub_expression->evaluate_as_integer();
            }

            llvm::Value* Parenthesis::generate_IR_address(llvm::IRBuilder<>* builder)
            {
                return sub_expression->generate_IR_address(builder);
            }

            const semantic_analysis::Type* Parenthesis::get_semantic_type()
            {
                return sub_expression->get_semantic_type();
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
