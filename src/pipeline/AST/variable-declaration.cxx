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
                Declaration(pipeline, std::move(location), Declaration::Kind::Variable, name, type),
                variable(nullptr)
            {

            }

            void VariableDeclaration::check_semantics()
            {
                Declaration::check_semantics();
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
                // auto type = this->type->get_semantic_type();
                // TODO this works only for atom types! expand also for others
                auto type = llvm::Type::getInt64Ty(builder->getContext());
                variable = builder->CreateAlloca(type, nullptr, util::String::format("v%zu", this->id).c_str());
            }
        }
    }
}
