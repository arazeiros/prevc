#include <prevc/pipeline/AST/type-declaration.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            TypeDeclaration::TypeDeclaration(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type):
                Declaration(pipeline, std::move(location), Declaration::Kind::Type, name, type)
            {

            }

            void TypeDeclaration::check_semantics()
            {
                Declaration::check_semantics();
            }

            util::String TypeDeclaration::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "type-declaration", "location": %s, "name": "%s", "declarationType": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
