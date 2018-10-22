
#ifndef PREVC_PIPELINE_AST_ARRAYTYPE_HXX
#define PREVC_PIPELINE_AST_ARRAYTYPE_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief The array type node in an AST.
             * */
            class ArrayType: public Type
            {
            public:
                /**
                 * \brief Create an AST array type node at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the node in the source code.
                 * \param size_expression The expression that represents the size of the array.
                 * \param type The type of the array.
                 * */
                ArrayType(Pipeline* pipeline, util::Location&& location, Expression* size_expression, Type* type);

                /**
                 * \brief Release used resources.
                 * */
                virtual ~ArrayType();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Returns a string representation of this array type.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The expression that represents the size of the array.
                 * */
                Expression* size_expression;

                /**
                 * \brief The type of the array.
                 * */
                Type* type;
            };
        }
    }
}

#endif
