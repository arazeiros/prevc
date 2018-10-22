#include <prevc/pipeline/AST/variable-declaration.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            VariableDeclaration::VariableDeclaration(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type):
                Declaration(pipeline, std::move(location), name, type)
            {

            }

            void VariableDeclaration::check_semantics()
            {
                // TODO ...
            }

            util::String VariableDeclaration::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "variable-declaration", "location": %s, "name": "%s", "declarationType": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
