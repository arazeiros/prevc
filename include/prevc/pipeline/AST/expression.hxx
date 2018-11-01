
#ifndef PREVC_PIPELINE_AST_EXPRESSION_HXX
#define PREVC_PIPELINE_AST_EXPRESSION_HXX

#include <cstdint>
#include <optional>
#include <llvm/IR/IRBuilder.h>
#include <prevc/pipeline/AST/node.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent an expression in the AST.
             * */
            class Expression: public Node
            {
            public:
                /**
                 * \brief Create an AST expression at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the expression in the source code.
                 * */
                Expression(Pipeline* pipeline, util::Location&& location);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Expression() = default;

                /**
                 * \brief Generate the IR code for this expression.
                 * \param builder The builder of the IR block containing this expression.
                 * \return The IR value representing this expression.
                 * */
                virtual llvm::Value* generate_IR(llvm::IRBuilder<>* builder) = 0;

                /**
                 * \brief Evaluate the expression as an integer (if possible).
                 * \return Returns the evaluated integer.
                 * */
                virtual std::optional<std::int64_t> evaluate_as_integer() const noexcept = 0;

                /**
                 * \brief Tells if the expression is lvalue or not.
                 * \return True if expression is lvalue, false otherwise.
                 * */
                virtual bool is_lvalue() const noexcept;

                /**
                 * \brief Returns the semantic type of this expression.
                 * \return The semantic type of this expression.
                 *
                 * Before this method can be called, the call to `check_semantics()` have to be done.
                 * */
                virtual const semantic_analysis::Type* get_semantic_type() = 0;
            };
        }
    }
}

#endif
