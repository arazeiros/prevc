#include <prevc/pipeline/AST/type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Type::Type(Pipeline* pipeline, util::Location&& location):
                Node(pipeline, std::move(location))
            {

            }
        }
    }
}
