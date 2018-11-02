#include <prevc/pipeline/AST/expression-statement.hxx>
#include <prevc/pipeline/semantic_analysis/type.hxx>
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

            void ExpressionStatement::check_semantics()
            {
                expression->check_semantics();

                auto expression_type = expression->get_semantic_type();

                if (!expression_type->is_void())
                    CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                            "statements must be of type `void`, but given is of type `%s`",
                            expression_type->to_string().c_str()));
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
