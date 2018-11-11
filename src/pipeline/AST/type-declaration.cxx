#include <prevc/pipeline/AST/type-declaration.hxx>
#include <prevc/pipeline/semantic_analysis/link-type.hxx>
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

            const semantic_analysis::Type* TypeDeclaration::generate_semantic_type()
            {
                return new semantic_analysis::LinkType(util::String(this->name));
            }

            const semantic_analysis::Type* TypeDeclaration::generate_real_semantic_type()
            {
                return type->generate_semantic_type(false);
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
