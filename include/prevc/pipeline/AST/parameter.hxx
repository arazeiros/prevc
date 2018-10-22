
#ifndef PREVC_PIPELINE_AST_PARAMETER_HXX
#define PREVC_PIPELINE_AST_PARAMETER_HXX

#include <prevc/pipeline/AST/variable-declaration.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a parameter in the AST.
             * */
            class Parameter: public VariableDeclaration
            {
            public:
                /**
                 * \brief Create an AST parameter at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the parameter in the source code.
                 * \param name The parameter name.
                 * \param type The parameter type.
                 * */
                Parameter(Pipeline* pipeline, util::Location&& location, const util::String& name, Type* type);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Parameter() = default;

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Returns a string representation of this parameter.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#endif
