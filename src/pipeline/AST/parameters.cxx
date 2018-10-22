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

            void Parameters::check_semantics()
            {
                for (auto& parameter : *this)
                    parameter->check_semantics();
            }
        }
    }
}
