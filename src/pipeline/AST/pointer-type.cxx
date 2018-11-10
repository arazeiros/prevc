#include <prevc/pipeline/AST/pointer-type.hxx>
#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
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
                type->check_semantics();
            }

            util::String PointerType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "pointer-type", "location": %s, "data_type": %s})",
                        location.to_string().c_str(),
                        type->to_string().c_str());
            }

            util::String PointerType::to_semantic_string() const noexcept
            {
                static util::String s_ptr = "ptr ";
                return s_ptr + type->to_semantic_string();
            }

            const semantic_analysis::Type* PointerType::generate_semantic_type() const noexcept
            {
                return pipeline->type_system->get_or_insert(to_semantic_string(), [this] ()
                    {
                        return new semantic_analysis::PointerType(this->type->get_semantic_type());
                    });
            }
        }
    }
}
