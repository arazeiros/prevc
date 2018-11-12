#include <prevc/pipeline/AST/component-access.hxx>
#include <prevc/pipeline/semantic_analysis/record-type.hxx>
#include <prevc/error.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            ComponentAccess::ComponentAccess(Pipeline* pipeline, util::Location&& location,
                    Expression* record, const util::String& component):
                Expression(pipeline, std::move(location)),
                record(record),
                component(component),
                record_type(nullptr),
                accessed_component_type(nullptr)
            {

            }

            ComponentAccess::~ComponentAccess()
            {
                delete record;
            }

            void ComponentAccess::check_semantics()
            {
                record->check_semantics();

                auto record_type = record->get_semantic_type();

                if (!record_type->is_record())
                    CompileTimeError::raise(pipeline->file_name, location,
                            "trying to perform a component access, but the given expression is not a record");

                this->record_type = record_type->as_record();
                auto component_type_optional = this->record_type->get_type_of(component);

                if (!component_type_optional.has_value())
                    CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                            "trying to perform a component access, but the given component name `%s` is not "
                            "present in the record type `%s`", component.c_str(), record_type->to_string().c_str()));

                accessed_component_type = component_type_optional.value();
            }

            llvm::Value* ComponentAccess::generate_IR(llvm::IRBuilder<>* builder)
            {
                return builder->CreateLoad(generate_IR_address(builder));
            }

            std::optional<int64_t> ComponentAccess::evaluate_as_integer() const noexcept
            {
                return {};
            }

            bool ComponentAccess::is_lvalue() const noexcept
            {
                return record->is_lvalue();
            }

            llvm::Value* ComponentAccess::generate_IR_address(llvm::IRBuilder<> *builder)
            {
                auto& context = builder->getContext();
                auto type     = ((semantic_analysis::Type*) this->record_type)->get_llvm_type(context);
                auto record   = this->record->generate_IR_address(builder);
                auto index    = this->record_type->get_index_of(component);
                return builder->CreateStructGEP(type, record, (unsigned int) index);
            }

            const semantic_analysis::Type* ComponentAccess::get_semantic_type()
            {
                return accessed_component_type;
            }

            util::String ComponentAccess::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "component-access", "location": %s, "record": %s, "component": "%s"})",
                        location.to_string().c_str(),
                        record->to_string().c_str(),
                        component.c_str());
            }
        }
    }
}
