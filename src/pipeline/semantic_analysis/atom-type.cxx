#include <prevc/pipeline/semantic_analysis/atom-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static constexpr size_t get_atom_kind_size(AtomType::Kind kind)
            {
                switch (kind)
                {
                    case AtomType::Kind::VOID: return 0;
                    case AtomType::Kind::BOOL: return 1;
                    case AtomType::Kind::CHAR: return 1;
                    case AtomType::Kind::INT:  return 8;
                }
            }

            AtomType::AtomType(Kind kind):
                Type(Type::Kind::ATOM, get_atom_kind_size(kind)),
                atomKind(kind)
            {

            }

            bool AtomType::can_be_assigned() const
            {
                return atomKind != AtomType::Kind::VOID;
            }

            bool AtomType::can_be_passed() const
            {
                return atomKind != AtomType::Kind::VOID;
            }

            bool AtomType::can_be_returned() const
            {
                return true;
            }
        }
    }
}
