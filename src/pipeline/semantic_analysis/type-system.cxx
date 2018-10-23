#include <prevc/pipeline/semantic_analysis/type-system.hxx>
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
                auto searched = types.find(&type);

                if (searched != types.end())
                    return searched->second;

                auto real_type = new Type(std::move(type));
                auto inserted = types.insert(std::make_pair(real_type, real_type));
                return inserted.first->second;
            }

            const Type* TypeSystem::get(const util::String& type)
            {
                return get(util::String(type));
            }
        }
    }
}
