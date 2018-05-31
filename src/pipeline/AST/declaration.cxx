#include <prevc/pipeline/AST/declaration.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Declaration::Declaration(Pipeline* pipeline, util::Location&& location):
                Node(pipeline, std::move(location))
            {

            }
        }
    }
}
