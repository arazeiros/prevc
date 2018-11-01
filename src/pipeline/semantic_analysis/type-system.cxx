#include <prevc/pipeline/semantic_analysis/type-system.hxx>
#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>
#include <cstring>
#include <utility>
#include <functional>
#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
#include <prevc/pipeline/semantic_analysis/array-type.hxx>
#include <prevc/pipeline/semantic_analysis/record-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            TypeSystem::TypeSystem() = default;

            TypeSystem::~TypeSystem()
            {
                for (auto& type : types)
                    delete type.second;
            }

            const Type* TypeSystem::get_or_insert(const util::String& id, std::function<const Type*()>&& provider)
            {
                auto searched = types.find(&id);

                if (searched != types.end())
                    return searched->second;

                auto real_type = provider();

                if (real_type == nullptr)
                    return nullptr;

                auto inserted = types.insert(std::make_pair(&real_type->id, real_type));
                return inserted.first->second;
            }
        }
    }
}
