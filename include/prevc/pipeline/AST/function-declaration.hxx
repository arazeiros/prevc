
#ifndef PREVC_PIPELINE_AST_FUNCTIONDECLARATION_HXX
#define PREVC_PIPELINE_AST_FUNCTIONDECLARATION_HXX

#include <prevc/pipeline/AST/declaration.hxx>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/parameters.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a function declaration in the AST.
             * */
            class FunctionDeclaration: public Declaration
            {
            public:
                /**
                 * \brief Create an AST declaration at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the declaration in the source code.
                 * \param name The function declaration name.
                 * \param type The function declaration type.
                 * \param parameters The function parameters.
                 * \param implementation The implementation of the function, or NULL if there is no implementation provided.
                 * */
                FunctionDeclaration(Pipeline* pipeline, util::Location&& location, const util::String& name, Type* type,
                        AST::Parameters* parameters, Expression* implementation = nullptr);

                /**
                 * \brief Releases used resources.
                 * */
                virtual ~FunctionDeclaration();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Returns a string representation of this function declaration.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            protected:
                /**
                 * \brief The function parameters.
                 * */
                 AST::Parameters* parameters;

                 /**
                  * \brief The implementation of the function, or NULL if there is no implementation provided.
                  * */
                 AST::Expression* implementation;
            };
        }
    }
}

#endif
