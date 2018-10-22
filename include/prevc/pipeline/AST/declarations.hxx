
#ifndef PREVC_PIPELINE_AST_DECLARATIONS_HXX
#define PREVC_PIPELINE_AST_DECLARATIONS_HXX

#include <prevc/pipeline/AST/declaration.hxx>
#include <prevc/pipeline/AST/collection-node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent declarations in the AST.
             * */
            class Declarations: public CollectionNode<Declaration*>
            {
            public:
                /**
                 * \brief Create an AST declarations node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the declaration in the source code.
                 * \param declarations The declarations.
                 * */
                Declarations(Pipeline* pipeline, util::Location&& location, std::vector<Declaration*>&& declarations);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Declarations() = default;

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
