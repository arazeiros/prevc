
#ifndef PREVC_PIPELINE_AST_PARENTHESIS_HXX
#define PREVC_PIPELINE_AST_PARENTHESIS_HXX

#include <prevc/pipeline/AST/expression.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a unary operation node in the AST.
             * */
            class Parenthesis: public Expression
            {
            public:
                /**
                 * \brief Create a parenthesis node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the parenthesis in the source code.
                 * \param sub_expression The sub-expression contained in the parenthesis.
                 * */
                Parenthesis(Pipeline* pipeline, util::Location&& location, Expression* sub_expression);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~Parenthesis();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the IR code for this parenthesis expression.
                 * \param builder The builder of the IR block containing this parenthesis expression.
                 * \return The IR value representing this parenthesis expression.
                 * */
                virtual llvm::Value* generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Evaluate the expression as an integer (if possible).
                 * \return Returns the evaluated integer.
                 * */
                virtual std::optional<std::int64_t> evaluate_as_integer() const noexcept override;

                /**
                 * \brief Generate the IR code for this expression (returning the address of the expression).
                 * \param builder The builder of the IR block containing this expression.
                 * \return The IR address representing this expression.
                 *
                 * The expression must be lvalue, otherwise this function has unexpected behaviour.
                 * */
                virtual llvm::Value* generate_IR_address(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Returns the semantic type of this expression.
                 * \return The semantic type of this expression.
                 *
                 * Before this method can be called, the call to `check_semantics()` have to be done.
                 * */
                virtual const semantic_analysis::Type* get_semantic_type() override;

                /**
                 * \brief Returns a string representation of this parenthesis.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The sub-expression contained in the parenthesis.
                 * */
                Expression* sub_expression;
            };
        }
    }
}

#endif
