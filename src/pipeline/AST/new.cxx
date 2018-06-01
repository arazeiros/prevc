#include <prevc/pipeline/AST/new.hxx>
#include <utility>
#include <llvm/IR/Constant.h>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            New::New(Pipeline* pipeline, util::Location&& location, Type* type):
                Expression(pipeline, std::move(location)),
                type(type)
            {

            }

            New::~New()
            {
                delete type;
            }

            llvm::Value* New::generate_IR(llvm::IRBuilder<> *builder)
            {
                // TODO implementation?
                // WARNING: this function just returns 'null'
                // to calculate the actual size to allocate the size of a type have to be known
                auto& context = pipeline->IR_module->getContext();
                return llvm::ConstantInt::get(context, llvm::APInt::getNullValue(8));
            }

            util::String New::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "new", "location": %s, "type": %s})",
                        location.to_string().c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
