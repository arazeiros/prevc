
#ifndef PREVC_PIPELINE_AST_VARIABLENAME_HXX
#define PREVC_PIPELINE_AST_VARIABLENAME_HXX

#include <prevc/error.hxx>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief A variable name in the AST.
             * */
            class VariableName: public Expression
            {
            public:
                /**
                 * \brief The lexeme of the atom.
                 * */
                const util::String name;

                /**
                 * \brief Create a variable name node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the variable name in the source code.
                 * \param name The name of the variable.
                 * */
                VariableName(Pipeline* pipeline, util::Location&& location, const util::String& name);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~VariableName();

                /**
                 * \brief Generate the IR code for this expression.
                 * \param builder The builder of the IR block containing this expression.
                 * \return The IR value representing this expression.
                 * */
                virtual llvm::Value* generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Returns a string representation of this expression.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#endif
