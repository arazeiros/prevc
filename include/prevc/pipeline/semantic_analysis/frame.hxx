
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAME_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAME_HXX

#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <cstdint>
#include <vector>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instructions.h>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            class FunctionCall;
            class FunctionDeclaration;
            class VariableName;
        }

        namespace semantic_analysis
        {
            /**
             * \brief Represent a function frame.
             * */
            class Frame
            {
                friend AST::FunctionCall;
                friend AST::FunctionDeclaration;
                friend AST::VariableName;

            public:
                /**
                 * \brief The level of the frame.
                 * */
                const std::int32_t level;

                /**
                 * \brief The allocated llvm frame.
                 * */
                llvm::AllocaInst* allocated_frame;

                /**
                 * \brief Creates a new function frame.
                 * \brief The level of the frame.
                 * */
                Frame(std::int32_t level, Frame* static_link);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Frame() = default;

                /**
                 * \brief Allocate a new variable in the frame.
                 * \param variable The type of the variable to allocate.
                 * \return The index of the allocated variable.
                 * */
                std::uint64_t allocate_variable(const Type* variable);

                /**
                 * \brief Get the llvm type representing this frame.
                 * \param context The llvm context.
                 * */
                llvm::StructType* get_llvm_type(llvm::LLVMContext& context);

            private:
                /**
                 * \brief All the variables in the frame.
                 * */
                std::vector<const Type*> variables;

                /**
                 * \brief A mapping of `variables` that contains relative llvm-types.
                 * */
                std::vector<llvm::Type*> llvm_variables;

                /**
                 * \brief The llvm type representing this frame.
                 * */
                llvm::StructType* llvm_type;

                /**
                 * \brief The frame's static link.
                 * */
                Frame* static_link;
            };
        }
    }
}

#endif
