#include <prevc/pipeline/AST/component.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Component::Component(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type):
                VariableDeclaration(pipeline, std::move(location), name, type)
            {

            }

            void Component::check_semantics()
            {
                VariableDeclaration::check_semantics();
            }

            bool Component::is_component_declaration() const noexcept
            {
                return true;
            }

            util::String Component::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "component", "location": %s, "name": "%s", "data_type": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
