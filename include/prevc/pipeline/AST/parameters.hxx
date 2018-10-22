
#ifndef PREVC_PIPELINE_AST_PARAMETERS_HXX
#define PREVC_PIPELINE_AST_PARAMETERS_HXX

#include <prevc/pipeline/AST/parameter.hxx>
#include <prevc/pipeline/AST/collection-node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent parameters in the AST.
             * */
            class Parameters: public CollectionNode<Parameter*>
            {
            public:
                /**
                 * \brief Create an AST parameters node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the parameters in the source code.
                 * \param parameters The parameters.
                 * */
                Parameters(Pipeline* pipeline, util::Location&& location, std::vector<Parameter*>&& parameters);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Parameters() = default;

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;
            };
        }
    }
}

#endif
