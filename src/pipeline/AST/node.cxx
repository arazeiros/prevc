#include <prevc/pipeline/AST/node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Node::Node(Pipeline* pipeline, util::Location&& location):
                pipeline(pipeline),
                location(std::move(location))
            {

            }
        }
    }
}
