
#ifndef PREVC_PIPELINE_AST_COMPONENTACCESS_HXX
#define PREVC_PIPELINE_AST_COMPONENTACCESS_HXX

#include <prevc/pipeline/AST/expression.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            class ComponentAccess: public Expression
            {
            public:
                /**
                 * \brief Create a component access node in the AST.
                 * \param location The location of the node.
                 * \param record The expression representing the accessed record.
                 * \param component The name of the accessing component.
                 * */
                ComponentAccess(Pipeline* pipeline, util::Location&& location, Expression* record, const util::String& component);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~ComponentAccess();

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
                 * \brief Tells if the expression is lvalue or not.
                 * \return True if expression is lvalue, false otherwise.
                 * */
                virtual bool is_lvalue() const noexcept;

                /**
                 * \brief Returns a string representation of this expression.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The expression representing the accessed record.
                 * */
                Expression* record;

                /**
                 * \brief The name of the component to access.
                 * */
                const util::String component;
            };
        }
    }
}

#endif
