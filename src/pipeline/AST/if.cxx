#include <prevc/pipeline/AST/if.hxx>
#include <prevc/pipeline/semantic_analysis/concrete-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            If::If(Pipeline* pipeline, util::Location&& location, Expression* condition,
                    Statements* then_body, Statements* else_body):
                Statement(pipeline, std::move(location)),
                condition(condition),
                then_body(then_body),
                else_body(else_body)
            {

            }

            If::~If()
            {
                delete condition;
                delete then_body;

                if (else_body != nullptr)
                    delete else_body;
            }

            void If::check_semantics()
            {
                condition->check_semantics();
                then_body->check_semantics();

                if (else_body != nullptr)
                    else_body->check_semantics();

                const auto& condition_type = condition->get_semantic_type();

                if (!condition_type->is_bool())
                    CompileTimeError::raise(pipeline->file_name, condition->location, util::String::format(
                            "condition expressions of if-statements must be of type `bool`, "
                            "the given expression is of type `%s`",
                            condition_type->to_string().c_str()));
            }

            void If::generate_IR(llvm::IRBuilder<>* builder)
            {
                // TODO implement...
            }

            util::String If::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "if", "location": %s, "condition": %s, "then_body": %s, "else_body": %s})",
                        location.to_string().c_str(),
                        condition->to_string().c_str(),
                        then_body->to_string().c_str(),
                        else_body == nullptr
                            ? "null"
                            : else_body->to_string().c_str());
            }
        }
    }
}
