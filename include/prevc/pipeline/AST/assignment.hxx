
#ifndef PREVC_PIPELINE_AST_ASSIGNMENT_HXX
#define PREVC_PIPELINE_AST_ASSIGNMENT_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/statement.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief An assignment statement in the AST.
             * */
            class Assignment: public Statement
            {
            public:

                /**
                 * \brief Create an assignment statement node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the assignment in the source code.
                 * \param destination The destination of the assignment.
                 * \param source The source of the assignment.
                 * */
                Assignment(Pipeline* pipeline, util::Location&& location, Expression* destination, Expression* source);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~Assignment();

                /**
                 * \brief Generate the IR code for this assignment statement expression.
                 * \param builder The builder of the IR block containing this assignment statement.
                 * */
                virtual void generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Returns a string representation of this assignment statement.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The destination of the assignment.
                 * */
                 Expression* destination;

                /**
                 * \brief The source of the assignment.
                 * */
                 Expression* source;
            };
        }
    }
}

#endif
