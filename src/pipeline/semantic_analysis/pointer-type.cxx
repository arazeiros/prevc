#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static inline util::String to_semantic_string(const Type* sub)
            {
                static const util::String s_ptr = "ptr ";
                return s_ptr + sub->to_string();
            }

            PointerType::PointerType(const Type* sub):
                Type(to_semantic_string(sub), Type::Kind::POINTER),
                sub(sub)
            {

            }

            bool PointerType::can_be_assigned() const
            {
                return true;
            }

            bool PointerType::can_be_passed() const
            {
                return true;
            }

            bool PointerType::can_be_returned() const
            {
                return true;
            }

            util::String PointerType::to_string() const noexcept
            {
                return id;
            }
        }
    }
}
