#include <prevc/pipeline/AST/if.hxx>
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
