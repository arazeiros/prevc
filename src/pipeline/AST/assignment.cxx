#include <prevc/pipeline/AST/assignment.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Assignment::Assignment(Pipeline* pipeline, util::Location&& location, Expression* destination, Expression* source):
                Statement(pipeline, std::move(location)),
                destination(destination),
                source(source)
            {

            }

            Assignment::~Assignment()
            {
                delete destination;
                delete source;
            }

            void Assignment::check_semantics()
            {
                destination->check_semantics();
                source->check_semantics();

                if (!destination->is_lvalue())
                    CompileTimeError::raise(pipeline->file_name, location,
                            "destination expression of the assignment is not assignable (not a lvalue)");

                // TODO check that destination is LValue
                // TODO that types of destination and source are compatible
            }

            void Assignment::generate_IR(llvm::IRBuilder<>* builder)
            {
                // auto destination_value = destination->generate_IR(builder);
                // auto source_value = source->generate_IR(builder);
                // TODO implement...
            }

            util::String Assignment::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "assignment", "location": %s, "destination": %s, "source": %s})",
                        location.to_string().c_str(),
                        destination->to_string().c_str(),
                        source->to_string().c_str());
            }
        }
    }
}
