#include <prevc/pipeline/AST/expression.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            Expression::Expression(Pipeline* pipeline, util::Location&& location):
                Node(pipeline, std::move(location))
            {

            }

            bool Expression::is_lvalue() const noexcept
            {
                return false;
            }

            llvm::Value* Expression::generate_IR_address(llvm::IRBuilder<> *builder)
            {
                InternalError::raise("trying to generate IR address of incompatible expression");
                return nullptr;
            }
        }
    }
}
