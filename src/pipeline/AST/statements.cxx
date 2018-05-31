#include <prevc/pipeline/AST/statements.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Statements::Statements(Pipeline* pipeline, util::Location&& location, std::vector<Statement*>&& nodes):
                CollectionNode(pipeline, std::move(location), std::move(nodes))
            {

            }
        }
    }
}
