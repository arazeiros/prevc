#include <prevc/pipeline/semantic_analysis/atom-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            static util::String to_semantic_string(AtomType::Kind kind)
            {
                switch (kind)
                {
                    case AtomType::Kind::VOID: return "void";
                    case AtomType::Kind::BOOL: return "bool";
                    case AtomType::Kind::CHAR: return "char";
                    case AtomType::Kind::INT:  return "int";
                }
            }

            AtomType::AtomType(Kind kind):
                Type(to_semantic_string(kind), Type::Kind::ATOM),
                atomKind(kind)
            {

            }

            bool AtomType::equals(const Type& other) const noexcept
            {
                if (other.kind != Type::Kind::ATOM)
                    return false;

                return this->atomKind == ((const AtomType*) &other)->atomKind;
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

            util::String AtomType::to_string() const noexcept
            {
                return id;
            }
        }
    }
}
