
#ifndef PREVC_PIPELINE_AST_NEW_HXX
#define PREVC_PIPELINE_AST_NEW_HXX

#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent an new-expression in the AST.
             * */
            class New: public Expression
            {
            public:
                /**
                 * \brief Create an AST new-expression at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the expression in the source code.
                 * \param type The type of the new-allocation.
                 * */
                New(Pipeline* pipeline, util::Location&& location, Type* type);

                /**
                 * \brief Release the used resources.
                 * */
                virtual ~New();

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
                 * \brief Returns the semantic type of this expression.
                 * \return The semantic type of this expression.
                 *
                 * Before this method can be called, the call to `check_semantics()` have to be done.
                 * */
                virtual const semantic_analysis::Type* get_semantic_type() override;

                /**
                 * \brief Returns a string representation of this primitive type.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief The type of the new-allocation.
                 * */
                Type* type;
            };
        }
    }
}

#endif
