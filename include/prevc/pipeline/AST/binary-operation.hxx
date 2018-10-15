
#ifndef PREVC_PIPELINE_AST_BINARYOPERATION_HXX
#define PREVC_PIPELINE_AST_BINARYOPERATION_HXX

#include <prevc/error.hxx>
#include <prevc/pipeline/AST/expression.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a binary operation in the AST.
             * */
            class BinaryOperation: public Expression
            {
            public:
                /**
                 * \brief The enumeration of all possible binary operators.
                 * */
                enum class Operator
                {
                    OR,
                    XOR,
                    AND,
                    EQU,
                    NEQ,
                    LTH,
                    LEQ,
                    GTH,
                    GEQ,
                    ADD,
                    SUBTRACT,
                    MULTIPLY,
                    DIVIDE,
                    MODULE,
                };

                /**
                 * \brief Create a binary operation node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the binary operation in the source code.
                 * \param operator_ The operator applied on the sub-expressions.
                 * \param left_expression The left sub-expression.
                 * \param right_expression The right sub-expression.
                 * */
                BinaryOperation(Pipeline* pipeline, util::Location&& location, Operator operator_, Expression* left_expression,
                        Expression* right_expression);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~BinaryOperation();

                /**
                 * \brief Generate the IR code for this binary operation expression.
                 * \param builder The builder of the IR block containing this binary operation expression.
                 * \return The IR value representing this binary operation expression.
                 * */
                virtual llvm::Value* generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Evaluate the expression as an integer (if possible).
                 * \return Returns the evaluated integer.
                 * */
                virtual std::optional<std::int64_t> evaluate_as_integer() const noexcept override;

                /**
                 * \brief Returns a string representation of this operation.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The operator applied on the sub-expressions.
                 * */
                Operator operator_;

                /**
                 * \brief The left sub-expression.
                 * */
                Expression* left_expression;

                /**
                 * \brief The right sub-expression.
                 * */
                Expression* right_expression;
            };

            /**
             * \brief Returns the C-string representation of a specified operator.
             * \param operator_ The specified operator.
             * \return The C-string representation.
             * */
            constexpr static const char* to_string(const BinaryOperation::Operator& operator_)
            {
                switch (operator_)
                {
                    case BinaryOperation::Operator::OR:       return "OR";
                    case BinaryOperation::Operator::XOR:      return "XOR";
                    case BinaryOperation::Operator::AND:      return "AND";
                    case BinaryOperation::Operator::EQU:      return "EQU";
                    case BinaryOperation::Operator::NEQ:      return "NEQ";
                    case BinaryOperation::Operator::LTH:      return "LTH";
                    case BinaryOperation::Operator::LEQ:      return "LEQ";
                    case BinaryOperation::Operator::GTH:      return "GTH";
                    case BinaryOperation::Operator::GEQ:      return "GEQ";
                    case BinaryOperation::Operator::ADD:      return "ADD";
                    case BinaryOperation::Operator::SUBTRACT: return "SUBTRACT";
                    case BinaryOperation::Operator::MULTIPLY: return "MULTIPLY";
                    case BinaryOperation::Operator::DIVIDE:   return "DIVIDE";
                    case BinaryOperation::Operator::MODULE:   return "MODULE";

                    default:
                        prevc::InternalError::raise("token not recognized");
                }
            }
        }
    }
}

#endif
