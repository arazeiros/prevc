#include <prevc/pipeline/semantic_analysis/frame.hxx>
#include <llvm/IR/DerivedTypes.h>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            Frame::Frame(std::int32_t level, Frame* static_link):
                level(level),
                allocated_frame(nullptr),
                static_link(static_link),
                llvm_type(nullptr)
            {
                // reserve the index for the static link
                this->allocate_variable(nullptr);
            }

            std::uint64_t Frame::allocate_variable(const Type* variable)
            {
                std::uint64_t index = this->variables.size();
                this->variables.push_back(variable);
                return index;
            }

            llvm::StructType* Frame::get_llvm_type(llvm::LLVMContext& context)
            {
                if (this->llvm_type != nullptr)
                    return this->llvm_type;

                auto count = this->variables.size();
                this->llvm_variables.reserve(count);

                this->llvm_variables.push_back(llvm::PointerType::getUnqual(
                        (this->static_link == nullptr)
                        ? llvm::Type::getVoidTy(context)
                        : this->static_link->get_llvm_type(context)));

                for (size_t i = 1; i < count; ++i)
                {
                    auto variable = (Type*) this->variables[i];
                    this->llvm_variables.push_back(variable->get_llvm_type(context));
                }

                this->llvm_type = llvm::StructType::create(context, this->llvm_variables);
                return this->llvm_type;
            }
        }
    }
}
