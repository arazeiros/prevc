#include <prevc/pipeline/AST/component-access.hxx>
#include <utility>
#include <prevc/error.hxx>

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
                component(component)
            {

            }

            ComponentAccess::~ComponentAccess()
            {
                delete record;
            }

            void ComponentAccess::check_semantics()
            {
                record->check_semantics();

                // TODO check if the component is present in the record
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
