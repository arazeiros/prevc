
#ifndef PREVC_PIPELINE_AST_NODE_HXX
#define PREVC_PIPELINE_AST_NODE_HXX

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            class Node;
        }
    }
}

#include <prevc/pipeline/pipeline.hxx>
#include <prevc/util/location.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The super class of every node in an AST.
             * */
            class Node
            {
            public:
                /**
                 * \brief The location of the node in the source code.
                 * */
                const util::Location location;

                /**
                 * \brief Create an AST node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * */
                Node(Pipeline* pipeline, util::Location&& location);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Node() = default;

                /**
                 * \brief Returns a string representation of this node.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept = 0;

            protected:
                /**
                 * \brief The pipeline that owns this AST node.
                 * */
                Pipeline* pipeline;
            };
        }
    }
}

#endif
