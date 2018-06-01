
#ifndef PREVC_PIPELINE_AST_VARIABLEDECLARATION_HXX
#define PREVC_PIPELINE_AST_VARIABLEDECLARATION_HXX

#include <prevc/pipeline/AST/declaration.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a variable declaration in the AST.
             * */
            class VariableDeclaration: public Declaration
            {
            public:
                /**
                 * \brief Create an AST declaration at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the declaration in the source code.
                 * \param name The variable declaration name.
                 * \param type The variable declaration type
                 * */
                VariableDeclaration(Pipeline* pipeline, util::Location&& location, const util::String& name, Type* type);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~VariableDeclaration() = default;

                /**
                 * \brief Returns a string representation of this variable declaration.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#endif
