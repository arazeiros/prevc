#include <prevc/pipeline/semantic_analysis/array-type.hxx>
#include <llvm/IR/DerivedTypes.h>
#include <sstream>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static inline util::String to_semantic_string(const Type* sub, size_t length)
            {
                std::stringstream stream;
                stream << "arr [";
                stream << length;
                stream << "] ";
                stream << sub->get_id().c_str();
                return stream.str();
            }

            ArrayType::ArrayType(const Type* sub, size_t length):
                ConcreteType(to_semantic_string(sub, length), Type::Kind::ARRAY),
                sub(sub),
                length(length)
            {

            }

            bool ArrayType::equals(const Type* other) const noexcept
            {
                if (!other->is_array())
                    return false;

                auto other_array = other->as_array();

                if (this == other_array)
                    return true;

                if (other_array->length != length)
                    return false;

                return this->sub->equals(other_array->sub);
            }

            bool ArrayType::is_cyclic(std::set<const LinkType *>* set) const noexcept
            {
                return this->sub->is_cyclic(set);
            }

            util::String ArrayType::to_string() const noexcept
            {
                return get_id();
            }

            llvm::Type* ArrayType::generate_llvm_type(llvm::LLVMContext& context)
            {
                return llvm::ArrayType::get(((Type*) sub)->get_llvm_type(context), length);
            }
        }
    }
}
