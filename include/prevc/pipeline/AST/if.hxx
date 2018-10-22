
#ifndef PREVC_PIPELINE_AST_IF_HXX
#define PREVC_PIPELINE_AST_IF_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/statements.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief An if-statement in the AST.
             * */
            class If: public Statement
            {
            public:

                /**
                 * \brief Create an if-statement node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the if-statement in the source code.
                 * \param condition The condition of the if-statement.
                 * \param then_body The then-body of the if-statement.
                 * \param else_body The else-body of the if-statement. NULL if not present.
                 * */
                If(Pipeline* pipeline, util::Location&& location, Expression* condition,
                        Statements* then_body, Statements* else_body = nullptr);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~If();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the IR code for this if statement expression.
                 * \param builder The builder of the IR block containing this if statement.
                 * */
                virtual void generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Returns a string representation of this if-statement.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The condition of the if-statement.
                 * */
                Expression* condition;

                /**
                 * \brief The then-body of the if-statement.
                 * */
                Statements* then_body;

                /**
                 * \brief The else-body of the if-statement. NULL if not present.
                 * */
                Statements* else_body;
            };
        }
    }
}

#endif
