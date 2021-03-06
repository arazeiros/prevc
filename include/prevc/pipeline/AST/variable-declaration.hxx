
#ifndef PREVC_PIPELINE_AST_VARIABLEDECLARATION_HXX
#define PREVC_PIPELINE_AST_VARIABLEDECLARATION_HXX

#include <llvm/IR/IRBuilder.h>
#include <prevc/pipeline/AST/declaration.hxx>
#include <prevc/pipeline/semantic_analysis/frame.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            /**
             * \brief Represent a variable declaration in the AST.
             * */
            class VariableDeclaration: public Declaration
            {
            public:
                /**
                 * \brief The frame containing this variable.
                 * */
                semantic_analysis::Frame* frame;

                /**
                 * \brief The index of the variable in the current frame.
                 *
                 * Contains -1 if it's undefined.
                 * */
                std::int64_t frame_index;

                /**
                 * \brief Create an AST declaration at the specified location.
                 * \param pipeline The pipeline that owns this AST node.
                 * \param location The location of the declaration in the source code.
                 * \param name The variable declaration name.
                 * \param type The variable declaration type
                 * */
                VariableDeclaration(Pipeline* pipeline, util::Location&& location, const util::String& name, Type* type);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~VariableDeclaration() = default;

                /**
                 * \brief Checks the semantics of the node.
                 * \param pipeline The pipeline of the node.
                 * */
                virtual void check_semantics() override;

                /**
                 * \brief Tells if this declaration is a component declaration.
                 * \return True if is it, false otherwise.
                 * */
                virtual bool is_component_declaration() const noexcept;

                /**
                 * \brief Returns a string representation of this variable declaration.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#endif
