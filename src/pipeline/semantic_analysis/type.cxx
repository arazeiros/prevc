#include <prevc/pipeline/semantic_analysis/type.hxx>
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
