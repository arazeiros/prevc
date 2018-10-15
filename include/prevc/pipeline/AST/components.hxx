
#ifndef PREVC_PIPELINE_AST_COMPONENTS_HXX
#define PREVC_PIPELINE_AST_COMPONENTS_HXX

#include <prevc/pipeline/AST/component.hxx>
#include <prevc/pipeline/AST/collection-node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent components in the AST.
             * */
            class Components: public CollectionNode<Component*>
            {
            public:
                /**
                 * \brief Create an AST components node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the components in the source code.
                 * \param components The components.
                 * */
                Components(Pipeline* pipeline, util::Location&& location, std::vector<Component*>&& components);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Components() = default;
            };
        }
    }
}

#endif
