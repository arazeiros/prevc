#include <prevc/pipeline/AST/variable-declaration.hxx>
#include <utility>
#include <prevc/pipeline/AST/parameter.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            VariableDeclaration::VariableDeclaration(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type):
                Declaration(pipeline, std::move(location), Declaration::Kind::Variable, name, type),
                frame(nullptr),
                frame_index(-1)
            {

            }

            void VariableDeclaration::check_semantics()
            {
                Declaration::check_semantics();

                if (is_component_declaration())
                    return;

                auto parameter = dynamic_cast<Parameter*>(this);

                if (parameter != nullptr)
                    return;

                auto access       = this->pipeline->frame_system->allocate_variable(get_semantic_type());
                this->frame       = access.first;
                this->frame_index = access.second;
            }

            bool VariableDeclaration::is_component_declaration() const noexcept
            {
                return false;
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
