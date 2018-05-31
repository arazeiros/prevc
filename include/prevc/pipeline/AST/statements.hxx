
#ifndef PREVC_PIPELINE_AST_STATEMENTS_HXX
#define PREVC_PIPELINE_AST_STATEMENTS_HXX

#include <prevc/pipeline/AST/statement.hxx>
#include <prevc/pipeline/AST/collection-node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a statement in the AST.
             * */
            class Statements: public CollectionNode<Statement*>
            {
            public:
                /**
                 * \brief Create an AST statement at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the statement in the source code.
                 * */
                Statements(Pipeline* pipeline, util::Location&& location, std::vector<Statement*>&& nodes);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Statements() = default;

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
