
#ifndef PREVC_PIPELINE_AST_ARGUMENTS_HXX
#define PREVC_PIPELINE_AST_ARGUMENTS_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/collection-node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent arguments in the AST.
             * */
            class Arguments: public CollectionNode<Expression*>
            {
            public:
                /**
                 * \brief Create an AST arguments node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the arguments in the source code.
                 * \param declarations The arguments.
                 * */
                Arguments(Pipeline* pipeline, util::Location&& location, std::vector<Expression*>&& arguments);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Arguments() = default;
            };
        }
    }
}

#endif
