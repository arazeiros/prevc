
#ifndef PREVC_PIPELINE_AST_STATEMENT_HXX
#define PREVC_PIPELINE_AST_STATEMENT_HXX

#include <llvm/IR/IRBuilder.h>
#include <prevc/pipeline/AST/node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a statement in the AST.
             * */
            class Statement: public Node
            {
            public:
                /**
                 * \brief Create an AST statement at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the statement in the source code.
                 * */
                Statement(Pipeline* pipeline, util::Location&& location);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Statement() = default;

                /**
                 * \brief Generate the IR code for this statement.
                 * \param builder The builder of the IR block containing this statement.
                 * */
                virtual void generate_IR(llvm::IRBuilder<>* builder) = 0;
            };
        }
    }
}

#endif
