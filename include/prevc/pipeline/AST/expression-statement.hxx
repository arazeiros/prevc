
#ifndef PREVC_PIPELINE_AST_EXPRESSIONSTATEMENT_HXX
#define PREVC_PIPELINE_AST_EXPRESSIONSTATEMENT_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/statement.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief An expression statement in the AST.
             * */
            class ExpressionStatement: public Statement
            {
            public:

                /**
                 * \brief Create an expression statement node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the atom in the source code.
                 * \param expression The contained expression.
                 * */
                ExpressionStatement(Pipeline* pipeline, util::Location&& location, Expression* expression);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~ExpressionStatement();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the IR code for this expression statement expression.
                 * \param builder The builder of the IR block containing this expression statement.
                 * */
                virtual void generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Returns a string representation of this expression statement.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The contained expression.
                 * */
                 Expression* expression;
            };
        }
    }
}

#endif
