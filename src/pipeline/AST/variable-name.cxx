#include <prevc/pipeline/AST/variable-name.hxx>
#include <utility>
#include <prevc/error.hxx>
#include <prevc/pipeline/AST/declaration.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            VariableName::VariableName(Pipeline* pipeline, util::Location&& location, const util::String& name):
                Expression(pipeline, std::move(location)),
                name(name),
                declaration(nullptr)
            {

            }

            VariableName::~VariableName() = default;

            void VariableName::check_semantics()
            {
                auto declaration_optional = pipeline->global_namespace->find_declaration(name);

                if (!declaration_optional.has_value())
                    CompileTimeError::raise(pipeline->file_name, location,
                            util::String::format("variable `%s` not declared", name.c_str()));

                auto declaration = declaration_optional.value();

                if (declaration->kind != Declaration::Kind::Variable)
                    CompileTimeError::raise(pipeline->file_name, location,
                            util::String::format("declared identifier `%s` is not a variable", name.c_str()));

                this->declaration = (VariableDeclaration*) declaration;
            }

            llvm::Value* VariableName::generate_IR(llvm::IRBuilder<>* builder)
            {
                return builder->CreateLoad(declaration->variable);
            }

            std::optional<int64_t> VariableName::evaluate_as_integer() const noexcept
            {
                return {};
            }

            bool VariableName::is_lvalue() const noexcept
            {
                // Should here be `true` always returned?
                // Can a variable name reference a component declaration? I think no.
                return !declaration->is_component_declaration();
            }

            const semantic_analysis::Type* VariableName::get_semantic_type()
            {
                return this->declaration->type->get_semantic_type();
            }

            util::String VariableName::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "variable-name", "location": %s, "name": "%s"})",
                        location.to_string().c_str(),
                        name.c_str());
            }
        }
    }
}
