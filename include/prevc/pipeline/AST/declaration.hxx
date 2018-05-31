
#ifndef PREVC_PIPELINE_AST_DECLARATION_HXX
#define PREVC_PIPELINE_AST_DECLARATION_HXX

#include <llvm/IR/IRBuilder.h>
#include <prevc/pipeline/AST/node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a declaration in the AST.
             * */
            class Declaration: public Node
            {
            public:
                /**
                 * \brief Create an AST declaration at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the declaration in the source code.
                 * */
                Declaration(Pipeline* pipeline, util::Location&& location);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Declaration() = default;
            };
        }
    }
}

#endif
