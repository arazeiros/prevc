#include <prevc/pipeline/AST/expression-statement.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            ExpressionStatement::ExpressionStatement(Pipeline* pipeline, util::Location&& location, Expression* expression):
                Statement(pipeline, std::move(location)),
                expression(expression)
            {

            }

            ExpressionStatement::~ExpressionStatement()
            {
                delete expression;
            }

            void ExpressionStatement::generate_IR(llvm::IRBuilder<>* builder)
            {
                expression->generate_IR(builder);
            }

            util::String ExpressionStatement::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "expression-statement", "location": %s, "expression": %s})",
                        location.to_string().c_str(),
                        expression->to_string().c_str());
            }
        }
    }
}
