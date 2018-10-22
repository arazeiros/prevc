#include <prevc/pipeline/AST/variable-name.hxx>
#include <utility>
#include <prevc/error.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            VariableName::VariableName(Pipeline* pipeline, util::Location&& location, const util::String& name):
                Expression(pipeline, std::move(location)),
                name(name)
            {

            }

            VariableName::~VariableName() = default;

            void VariableName::check_semantics()
            {
                // TODO ...
            }

            llvm::Value* VariableName::generate_IR(llvm::IRBuilder<>* builder)
            {
                // TODO implement
                InternalError::raise("missing implementation: AST variable name generating IR");
                return nullptr;
            }

            std::optional<int64_t> VariableName::evaluate_as_integer() const noexcept
            {
                return {};
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
