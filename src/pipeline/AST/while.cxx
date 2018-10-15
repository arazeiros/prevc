#include <prevc/pipeline/AST/while.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            While::While(Pipeline* pipeline, util::Location&& location, Expression* condition, Statements* body):
                Statement(pipeline, std::move(location)),
                condition(condition),
                body(body)
            {

            }

            While::~While()
            {
                delete condition;
                delete body;
            }

            void While::generate_IR(llvm::IRBuilder<>* builder)
            {
                // TODO implement...
            }

            util::String While::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "while", "location": %s, "condition": %s, "body": %s})",
                        location.to_string().c_str(),
                        condition->to_string().c_str(),
                        body->to_string().c_str());
            }
        }
    }
}
