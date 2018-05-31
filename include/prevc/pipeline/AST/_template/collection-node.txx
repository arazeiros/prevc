#include <prevc/pipeline/AST/collection-node.hxx>
#include <sstream>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            template <typename TNode>
            CollectionNode<TNode>::CollectionNode(Pipeline* pipeline, util::Location&& location, std::vector<NodeType>&& nodes):
                    Node(pipeline, std::move(location)),
                    std::vector<TNode>(std::move(nodes))
            {

            }

            template <typename TNode>
            CollectionNode<TNode>::~CollectionNode()
            {
                for (auto node : *this)
                    delete node;

                this->clear();
            }

            template <typename TNode>
            util::String CollectionNode<TNode>::to_string() const noexcept
            {
                std::stringbuf buffer;
                std::ostream out(&buffer);
                auto i = this->begin();
                auto n = this->end();
                out << "[";

                if (!this->empty())
                {
                    out << (**i).to_string().c_str();

                    while (++i != n)
                    {
                        out << ", ";
                        out << (**i).to_string().c_str();
                    }
                }

                out << "]";
                return buffer.str();
            }
        }
    }
}
