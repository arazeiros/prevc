
#ifndef PREVC_PIPELINE_AST_COMPOUND_HXX
#define PREVC_PIPELINE_AST_COMPOUND_HXX

#include <prevc/pipeline/AST/declarations.hxx>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/statements.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a compound node in the AST.
             * */
            class Compound: public Expression
            {
            public:
                /**
                 * \brief Create an compound expression node.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the compound in the source code.
                 * \param statements The compound's statements.
                 * \param expression The return expression of the compound.
                 * \param declarations The compound's declarations.
                 * */
                Compound(Pipeline* pipeline, util::Location&& location, Statements* statements,
                         Expression* expression, Declarations* declarations);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~Compound();

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Generate the IR code for this compound expression.
                 * \param builder The builder of the IR block containing this compound expression.
                 * \return The IR value representing this compound expression.
                 * */
                virtual llvm::Value* generate_IR(llvm::IRBuilder<>* builder) override;

                /**
                 * \brief Evaluate the expression as an integer (if possible).
                 * \return Returns the evaluated integer.
                 * */
                virtual std::optional<std::int64_t> evaluate_as_integer() const noexcept override;

                /**
                 * \brief Returns the semantic type of this expression.
                 * \return The semantic type of this expression.
                 *
                 * Before this method can be called, the call to `check_semantics()` have to be done.
                 * */
                virtual const semantic_analysis::Type* get_semantic_type() override;

                /**
                 * \brief Returns a string representation of this compound.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The compound's statements.
                 * */
                Statements* statements;

                /**
                 * \brief The return expression of the compound.
                 * */
                Expression* expression;

                /**
                 * \brief The compound's declarations.
                 * */
                Declarations* declarations;
            };
        }
    }
}

#endif
