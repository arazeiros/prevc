#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            Type::Type(util::String&& id, Kind kind):
                id(std::move(id)),
                kind(kind)
            {

            }

            bool Type::is_atom() const noexcept
            {
                return kind == Kind::ATOM;
            }

            bool Type::is_pointer() const noexcept
            {
                return kind == Kind::POINTER;
            }

            bool Type::is_array() const noexcept
            {
                return kind == Kind::ARRAY;
            }

            bool Type::is_record() const noexcept
            {
                return kind == Kind::RECORD;
            }

            bool Type::is_char() const noexcept
            {
                return kind == Kind::ATOM && ((const AtomType*) this)->atomKind == AtomType::Kind::CHAR;
            }

            bool Type::is_int() const noexcept
            {
                return kind == Kind::ATOM && ((const AtomType*) this)->atomKind == AtomType::Kind::INT;
            }

            bool Type::is_void() const noexcept
            {
                return kind == Kind::ATOM && ((const AtomType*) this)->atomKind == AtomType::Kind::VOID;
            }

            bool Type::is_bool() const noexcept
            {
                return kind == Kind::ATOM && ((const AtomType*) this)->atomKind == AtomType::Kind::BOOL;
            }

            bool Type::can_be_assigned() const
            {
                return false;
            }

            bool Type::can_be_passed() const
            {
                return false;
            }

            bool Type::can_be_returned() const
            {
                return false;
            }
        }
    }
}
