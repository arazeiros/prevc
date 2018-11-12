
#ifndef PREVC_PIPELINE_AST_COMPONENTACCESS_HXX
#define PREVC_PIPELINE_AST_COMPONENTACCESS_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/component.hxx>

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

                /**
                 * \brief The semantic record type.
                 * */
                const semantic_analysis::RecordType* record_type;

                /**
                 * \brief The type of the component accessed by this expression.
                 *
                 * Calculated during semantic-analysis, by `check_semantics()`
                 * */
                const semantic_analysis::Type* accessed_component_type;
            };
        }
    }
}

#endif
