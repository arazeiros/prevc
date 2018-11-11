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
                ConcreteType(to_semantic_string(sub), Type::Kind::POINTER),
                sub(sub)
            {

            }

            bool PointerType::equals(const Type* other) const noexcept
            {
                if (!other->is_pointer())
                    return false;

                auto other_type = other->as_pointer();

                if (this == other_type)
                    return true;

                return this->sub->equals(other_type->sub);
            }

            bool PointerType::is_cyclic(std::set<const LinkType *>* set) const noexcept
            {
                return false;
            }

            util::String PointerType::to_string() const noexcept
            {
                return get_id();
            }
        }
    }
}
