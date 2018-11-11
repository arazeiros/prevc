#include <prevc/pipeline/semantic_analysis/concrete-type.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            ConcreteType::ConcreteType(util::String&& id, Kind kind):
                id(std::move(id)),
                kind(kind)
            {

            }

            const util::String& ConcreteType::get_id() const noexcept
            {
                return id;
            }

            Type::Kind ConcreteType::get_kind() const noexcept
            {
                return kind;
            }
        }
    }
}
