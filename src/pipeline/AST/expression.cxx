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
        }
    }
}
