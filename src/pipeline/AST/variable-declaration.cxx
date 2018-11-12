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
                variable(nullptr),
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

                this->frame_index = (std::int64_t) this->pipeline->frame_system->allocate_variable(get_semantic_type());
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

            void VariableDeclaration::generate_IR(llvm::IRBuilder<> *builder)
            {
                auto type = ((semantic_analysis::Type*) this->type->get_semantic_type())
                        ->get_llvm_type(builder->getContext());

                variable = builder->CreateAlloca(type, nullptr, util::String::format("v%zu", this->id).c_str());
            }
        }
    }
}
