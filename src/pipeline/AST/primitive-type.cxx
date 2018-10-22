#include <prevc/pipeline/AST/primitive-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            PrimitiveType::PrimitiveType(Pipeline* pipeline, util::Location&& location, PrimitiveType::Name name):
                Type(pipeline, std::move(location)),
                name(name)
            {

            }

            void PrimitiveType::check_semantics()
            {
                // It's OK.
            }

            util::String PrimitiveType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "primitive-type", "location": %s, "name": "%s"})",
                        location.to_string().c_str(),
                        AST::to_string(name));
            }
        }
    }
}
