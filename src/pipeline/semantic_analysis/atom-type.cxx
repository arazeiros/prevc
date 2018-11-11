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
                ConcreteType(to_semantic_string(kind), Type::Kind::ATOM),
                atomKind(kind)
            {

            }

            bool AtomType::equals(const Type* other) const noexcept
            {
                if (!other->is_atom())
                    return false;

                return this->atomKind == other->as_atom()->atomKind;
            }

            bool AtomType::is_cyclic(std::set<const LinkType *>* set) const noexcept
            {
                return false;
            }

            util::String AtomType::to_string() const noexcept
            {
                return get_id();
            }
        }
    }
}
