
#ifndef PREVC_PIPELINE_AST_COLLECTIONNODE_HXX
#define PREVC_PIPELINE_AST_COLLECTIONNODE_HXX

#include <vector>
#include <prevc/pipeline/AST/node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief A node that represent a collection of AST nodes.
             * */
            template <typename TNode>
            class CollectionNode: public Node, protected std::vector<TNode>
            {
            public:
                typedef TNode NodeType;

                /**
                 * \brief Create collection of nodes.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the nodes.
                 * \param nodes The vector containing all the nodes.
                 * */
                CollectionNode(Pipeline* pipeline, util::Location&& location, std::vector<NodeType>&& nodes);

                /**
                 * \brief Delete all the nodes in the vector.
                 * */
                virtual ~CollectionNode();

                /**
                 * \brief Returns a string representation of this collection.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#include "_template/collection-node.txx"

#endif
