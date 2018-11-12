#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <prevc/pipeline/semantic_analysis/array-type.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>
#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
#include <prevc/pipeline/semantic_analysis/record-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            Type::Type():
                llvm_type(nullptr)
            {

            }

            bool Type::is_link() const noexcept
            {
                return false;
            }

            bool Type::is_array() const noexcept
            {
                return this->get_kind() == Type::Kind::ARRAY;
            }

            bool Type::is_atom() const noexcept
            {
                return this->get_kind() == Type::Kind::ATOM;
            }

            bool Type::is_record() const noexcept
            {
                return this->get_kind() == Type::Kind::RECORD;
            }

            bool Type::is_pointer() const noexcept
            {
                return this->get_kind() == Type::Kind::POINTER;
            }

            bool Type::is_void() const noexcept
            {
                if (!this->is_atom())
                    return false;

                return as_atom()->atomKind == AtomType::Kind::VOID;
            }

            bool Type::is_bool() const noexcept
            {
                if (!this->is_atom())
                    return false;

                return as_atom()->atomKind == AtomType::Kind::BOOL;
            }

            bool Type::is_char() const noexcept
            {
                if (!this->is_atom())
                    return false;

                return as_atom()->atomKind == AtomType::Kind::CHAR;
            }

            bool Type::is_int() const noexcept
            {
                if (!this->is_atom())
                    return false;

                return as_atom()->atomKind == AtomType::Kind::INT;
            }

            const AtomType* Type::as_atom() const
            {
                return dynamic_cast<const AtomType*>(this);
            }

            const ArrayType* Type::as_array() const
            {
                return dynamic_cast<const ArrayType*>(this);
            }

            const RecordType* Type::as_record() const
            {
                return dynamic_cast<const RecordType*>(this);
            }

            const PointerType* Type::as_pointer() const
            {
                return dynamic_cast<const PointerType*>(this);
            }

            bool Type::can_be_assigned() const
            {
                if (this->is_pointer())
                    return true;

                if (!this->is_atom())
                    return false;

                return !as_atom()->is_void();
            }

            bool Type::can_be_passed() const
            {
                if (this->is_pointer())
                    return true;

                if (!this->is_atom())
                    return false;

                return !as_atom()->is_void();
            }

            bool Type::can_be_returned() const
            {
                return this->is_pointer() || this->is_atom();
            }

            llvm::Type* Type::get_llvm_type(llvm::LLVMContext &context)
            {
                if (llvm_type == nullptr)
                    llvm_type = generate_llvm_type(context);

                return llvm_type;
            }
        }
    }
}
