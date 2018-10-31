#include <prevc/pipeline/semantic_analysis/type-system.hxx>
#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            TypeSystem::TypeSystem()
            {
                get("bool");
                get("char");
                get("int");
                get("void");
            }

            TypeSystem::~TypeSystem()
            {
                for (auto& type : types)
                    delete type.second;
            }

            const Type* TypeSystem::get(util::String&& type)
            {
                auto searched = types.find(type);

                if (searched != types.end())
                    return searched->second;

                auto real_type = generate(type);

                if (real_type == nullptr)
                    return nullptr;

                auto inserted = types.insert(std::make_pair(std::move(type), real_type));
                return inserted.first->second;
            }

            const Type* TypeSystem::get(const util::String& type)
            {
                return get(util::String(type));
            }

            const Type* TypeSystem::generate(const util::String& id)
            {
                if (id == "void")
                    return new AtomType(AtomType::Kind::VOID);
                else if (id == "bool")
                    return new AtomType(AtomType::Kind::BOOL);
                else if (id == "char")
                    return new AtomType(AtomType::Kind::CHAR);
                else if (id == "int")
                    return new AtomType(AtomType::Kind::INT);

                return nullptr;
            }
        }
    }
}
