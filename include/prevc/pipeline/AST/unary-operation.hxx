
#ifndef PREVC_PIPELINE_AST_UNARYOPERATION_HXX
#define PREVC_PIPELINE_AST_UNARYOPERATION_HXX

#include <prevc/error.hxx>
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
            class UnaryOperation: public Expression
            {
            public:
                /**
                 * \brief The enumeration of all possible unary operators.
                 * */
                enum class Operator
                {
                    PLUS,
                    MINUS,
                    NOT,
                    DEL,
                    MEM, // $ (in C is &)
                    VAL  // @ (in C is *)
                };

                /**
                 * \brief Create an unary operation node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the unary operation in the source code.
                 * \param operator_ The operator applied on the sub-expression.
                 * \param sub_expression The sub-expression on which the unary operation is executed.
                 * */
                UnaryOperation(Pipeline* pipeline, util::Location&& location, Operator operator_, Expression* sub_expression);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~UnaryOperation();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the IR code for this unary operation expression.
                 * \param builder The builder of the IR block containing this unary operation expression.
                 * \return The IR value representing this unary operation expression.
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
                 * \brief Returns a string representation of this operation.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The operator applied on the sub-expression.
                 * */
                Operator operator_;

                /**
                 * \brief The sub-expression on which the unary operation is executed.
                 * */
                Expression* sub_expression;
            };

            /**
             * \brief Returns the C-string representation of a specified operator.
             * \param operator_ The specified operator.
             * \return The C-string representation.
             * */
            constexpr static const char* to_string(const UnaryOperation::Operator& operator_)
            {
                switch (operator_)
                {
                    case UnaryOperation::Operator::PLUS:  return "PLUS";
                    case UnaryOperation::Operator::MINUS: return "MINUS";
                    case UnaryOperation::Operator::NOT:   return "NOT";
                    case UnaryOperation::Operator::DEL:   return "DEL";
                    case UnaryOperation::Operator::MEM:   return "MEM";
                    case UnaryOperation::Operator::VAL:   return "VAL";

                    default:
                        prevc::InternalError::raise("token not recognized");
                }
            }
        }
    }
}

#endif
