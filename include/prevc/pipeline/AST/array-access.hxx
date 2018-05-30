
#ifndef PREVC_PIPELINE_AST_ARRAYACCESS_HXX
#define PREVC_PIPELINE_AST_ARRAYACCESS_HXX

#include <prevc/pipeline/AST/expression.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            class ArrayAccess: public Expression
            {
            public:
                /**
                 * \brief Create an array access node in the AST.
                 * \param location The location of the node.
                 * \param array_expression The expression representing the accessed array.
                 * \param index_expression The expression representing the index of the accessed array's element.
                 * */
                ArrayAccess(util::Location&& location, Expression* array_expression, Expression* index_expression);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~ArrayAccess() = default;

            private:
                /**
                 * \brief The expression representing the accessed array.
                 * */
                Expression* array_expression;

                /**
                 * \brief The expression representing the index of the accessed array's element.
                 * */
                Expression* index_expression;
            };
        }
    }
}

#endif
