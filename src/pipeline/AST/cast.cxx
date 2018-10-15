#include <prevc/pipeline/AST/cast.hxx>
#include <utility>
#include <llvm/IR/Constant.h>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Cast::Cast(Pipeline* pipeline, util::Location&& location, Type* type, Expression* sub):
                Expression(pipeline, std::move(location)),
                type(type),
                sub(sub)
            {

            }

            Cast::~Cast()
            {
                delete type;
                delete sub;
            }

            llvm::Value* Cast::generate_IR(llvm::IRBuilder<> *builder)
            {
                return sub->generate_IR(builder);
            }

            std::optional<int64_t> Cast::evaluate_as_integer() const noexcept
            {
                return sub->evaluate_as_integer();
            }

            util::String Cast::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "cast", "location": %s, "castType": %s, "sub": %s})",
                        location.to_string().c_str(),
                        type->to_string().c_str(),
                        sub->to_string().c_str());
            }
        }
    }
}
