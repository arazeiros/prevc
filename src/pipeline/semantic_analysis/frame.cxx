#include <prevc/pipeline/semantic_analysis/frame.hxx>
#include <llvm/IR/DerivedTypes.h>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            Frame::Frame(std::int32_t level):
                level(level),
                allocated_frame(nullptr)
            {

            }

            std::uint64_t Frame::allocate_variable(const Type* variable)
            {
                std::uint64_t index = this->variables.size();
                this->variables.push_back(variable);
                return index;
            }

            llvm::Type* Frame::get_llvm_type(llvm::LLVMContext& context)
            {
                if (this->llvm_type != nullptr)
                    return this->llvm_type;

                for (auto& variable : this->variables)
                    this->llvm_variables.push_back(((Type*) variable)->get_llvm_type(context));

                this->llvm_type = llvm::StructType::create(context, this->llvm_variables);
                return this->llvm_type;
            }
        }
    }
}
