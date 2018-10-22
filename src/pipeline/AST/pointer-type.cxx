#include <prevc/pipeline/AST/pointer-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            PointerType::PointerType(Pipeline* pipeline, util::Location&& location, Type* type):
                Type(pipeline, std::move(location)),
                type(type)
            {

            }

            PointerType::~PointerType()
            {
                delete type;
            }

            void PointerType::check_semantics()
            {
                // TODO ...
                type->check_semantics();
            }

            util::String PointerType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "pointer-type", "location": %s, "data_type": %s})",
                        location.to_string().c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
