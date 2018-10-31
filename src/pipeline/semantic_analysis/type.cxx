#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            Type::Type(Kind kind, size_t size):
                kind(kind),
                size(size)
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
