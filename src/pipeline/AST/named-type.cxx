#include <prevc/pipeline/AST/named-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            NamedType::NamedType(Pipeline* pipeline, util::Location&& location, const util::String& name):
                Type(pipeline, std::move(location)),
                name(name)
            {

            }

            void NamedType::check_semantics()
            {
                // TODO ...
            }

            util::String NamedType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "pointer-type", "location": %s, "name": "%s"})",
                        location.to_string().c_str(),
                        name.c_str());
            }
        }
    }
}
