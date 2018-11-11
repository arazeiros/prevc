#include <prevc/pipeline/AST/assignment.hxx>
#include <prevc/pipeline/semantic_analysis/concrete-type.hxx>
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

                auto destination_type = destination->get_semantic_type();

                if (!destination_type->can_be_assigned())
                    CompileTimeError::raise(pipeline->file_name, destination->location, util::String::format(
                            "destination expression of the assignment is not assignable, is of type `%s`",
                            destination_type->to_string().c_str()));

                if (!destination->is_lvalue())
                    CompileTimeError::raise(pipeline->file_name, destination->location,
                            "destination expression of the assignment is not lvalue");

                auto source_type = source->get_semantic_type();

                if (!destination_type->equals(source_type))
                    CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                            "destination and source expressions of an assignment must have the same type, "
                            "but destination is of type `%s` and source of type `%s`",
                            destination_type->to_string().c_str(), source_type->to_string().c_str()));
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
