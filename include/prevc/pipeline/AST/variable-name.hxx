
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
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the IR code for this expression.
                 * \param builder The builder of the IR block containing this expression.
                 * \return The IR value representing this expression.
                 * */
                virtual llvm::Value* generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Evaluate the expression as an integer (if possible).
                 * \return Returns the evaluated integer.
                 * */
                virtual std::optional<std::int64_t> evaluate_as_integer() const noexcept override;

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
