#include <prevc/pipeline/AST/parameters.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Parameters::Parameters(Pipeline* pipeline, util::Location&& location, std::vector<Parameter*>&& parameters):
                CollectionNode(pipeline, std::move(location), std::move(parameters))
            {

            }
        }
    }
}
