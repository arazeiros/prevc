
#ifndef PREVC_PIPELINE_AST_ARRAYACCESS_HXX
#define PREVC_PIPELINE_AST_ARRAYACCESS_HXX

#include <prevc/pipeline/AST/expression.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            class ArrayAccess: public Expression
            {
            public:
                /**
                 * \brief Create an array access node in the AST.
                 * \param location The location of the node.
                 * \param array The expression representing the accessed array.
                 * \param index The expression representing the index of the accessed array's element.
                 * */
                ArrayAccess(Pipeline* pipeline, util::Location&& location, Expression* array, Expression* index);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~ArrayAccess();

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

            private:
                /**
                 * \brief The expression representing the accessed array.
                 * */
                Expression* array;

                /**
                 * \brief The expression representing the index of the accessed array's element.
                 * */
                Expression* index;
            };
        }
    }
}

#endif
