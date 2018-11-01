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

                auto component_type_optional = ((semantic_analysis::RecordType*) record_type)->get_type_of(component);

                if (!component_type_optional.has_value())
                    CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                            "trying to perform a component access, but the given component name `%s` is not "
                            "present in the record type `%s`", component.c_str(), record_type->to_string().c_str()));

                accessed_component_type = component_type_optional.value();
            }

            llvm::Value* ComponentAccess::generate_IR(llvm::IRBuilder<>* builder)
            {
                // TODO implement
                InternalError::raise("missing implementation: AST component access generating IR");
                return nullptr;
            }

            std::optional<int64_t> ComponentAccess::evaluate_as_integer() const noexcept
            {
                return {};
            }

            bool ComponentAccess::is_lvalue() const noexcept
            {
                return record->is_lvalue();
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
