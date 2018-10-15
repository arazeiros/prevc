
#ifndef PREVC_PIPELINE_AST_WHILE_HXX
#define PREVC_PIPELINE_AST_WHILE_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/statements.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief A while statement in the AST.
             * */
            class While: public Statement
            {
            public:

                /**
                 * \brief Create an while statement node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the assignment in the source code.
                 * \param condition The condition of the while statement.
                 * \param body The body of the while-statement.
                 * */
                While(Pipeline* pipeline, util::Location&& location, Expression* condition, Statements* body);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~While();

                /**
                 * \brief Generate the IR code for this while statement expression.
                 * \param builder The builder of the IR block containing this while statement.
                 * */
                virtual void generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Returns a string representation of this while statement.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The condition of the while-statement.
                 * */
                Expression* condition;

                /**
                 * \brief The body of the while-statement.
                 * */
                Statements* body;
            };
        }
    }
}

#endif
