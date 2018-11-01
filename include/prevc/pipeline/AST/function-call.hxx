
#ifndef PREVC_PIPELINE_AST_FUNCTIONCALL_HXX
#define PREVC_PIPELINE_AST_FUNCTIONCALL_HXX

#include <prevc/pipeline/AST/arguments.hxx>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/function-declaration.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief A function call in the AST.
             * */
            class FunctionCall: public Expression
            {
            public:
                /**
                 * \brief Create a function call node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the function call in the source code.
                 * \param name The name of the function.
                 * \param arguments The function call arguments.
                 * */
                FunctionCall(Pipeline* pipeline, util::Location&& location, const util::String& name, Arguments* arguments);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~FunctionCall();

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
                 * \brief Returns the semantic type of this expression.
                 * \return The semantic type of this expression.
                 *
                 * Before this method can be called, the call to `check_semantics()` have to be done.
                 * */
                virtual const semantic_analysis::Type* get_semantic_type() override;

                /**
                 * \brief Returns a string representation of this expression.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The name of the function.
                 * */
                util::String name;

                /**
                 * \brief The function call arguments.
                 * */
                Arguments* arguments;

                /**
                 * \brief Stores the declaration referenced by this function name.
                 * Calculated during semantic analysis.
                 * */
                FunctionDeclaration* declaration;
            };
        }
    }
}

#endif
