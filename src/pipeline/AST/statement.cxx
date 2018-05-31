#include <prevc/pipeline/AST/statement.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Statement::Statement(Pipeline* pipeline, util::Location&& location):
                Node(pipeline, std::move(location))
            {

            }
        }
    }
}
