
#ifndef PREVC_PIPELINE_AST_TYPE_HXX
#define PREVC_PIPELINE_AST_TYPE_HXX

#include <prevc/pipeline/AST/node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The type node in an AST.
             * */
            class Type: public Node
            {
            public:
                /**
                 * \brief Create an AST type node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * */
                Type(Pipeline* pipeline, util::Location&& location);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Type() = default;
            };
        }
    }
}

#endif
