#include <prevc/pipeline/AST/primitive-type.hxx>
#include <utility>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            PrimitiveType::PrimitiveType(Pipeline* pipeline, util::Location&& location, PrimitiveType::Name name):
                Type(pipeline, std::move(location)),
                name(name)
            {

            }

            void PrimitiveType::check_semantics()
            {
                // It's ok.
            }

            util::String PrimitiveType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "primitive-type", "location": %s, "name": "%s"})",
                        location.to_string().c_str(),
                        AST::to_string(name));
            }

            util::String PrimitiveType::to_semantic_string() const noexcept
            {
                switch (name)
                {
                    case Name::VOID: return "void";
                    case Name::BOOL: return "bool";
                    case Name::CHAR: return "char";
                    case Name::INT:  return "int";
                }
            }

            const semantic_analysis::Type* PrimitiveType::generate_semantic_type(bool cache) const noexcept
            {
                using SAtom = semantic_analysis::AtomType;

                switch (name)
                {
                    case PrimitiveType::Name::VOID:
                        return pipeline->type_system->get_or_insert("void", [] () { return new SAtom(SAtom::Kind::VOID); });

                    case PrimitiveType::Name::BOOL:
                        return pipeline->type_system->get_or_insert("bool", [] () { return new SAtom(SAtom::Kind::BOOL); });

                    case PrimitiveType::Name::CHAR:
                        return pipeline->type_system->get_or_insert("char", [] () { return new SAtom(SAtom::Kind::CHAR); });

                    case PrimitiveType::Name::INT:
                        return pipeline->type_system->get_or_insert("int", [] () { return new SAtom(SAtom::Kind::INT); });
                }
            }
        }
    }
}
