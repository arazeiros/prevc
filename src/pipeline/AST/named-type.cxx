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
                name(name),
                declaration(nullptr)
            {

            }

            void NamedType::check_semantics()
            {
                auto declaration_optional = pipeline->global_namespace->find_declaration(name);

                if (!declaration_optional.has_value())
                    CompileTimeError::raise(pipeline->file_name, location,
                            util::String::format("type `%s` not declared", name.c_str()));

                auto declaration = declaration_optional.value();

                if (declaration->kind != Declaration::Kind::Type)
                    CompileTimeError::raise(pipeline->file_name, location,
                                            util::String::format("declared identifier `%s` is not a type", name.c_str()));

                this->declaration = (TypeDeclaration*) declaration;
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
