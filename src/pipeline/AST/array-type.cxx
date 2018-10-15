#include <prevc/pipeline/AST/array-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            ArrayType::ArrayType(Pipeline* pipeline, util::Location&& location, Expression* size_expression, Type* type):
                Type(pipeline, std::move(location)),
                size_expression(size_expression),
                type(type)
            {

            }

            ArrayType::~ArrayType()
            {
                delete size_expression;
                delete type;
            }

            util::String ArrayType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "primitive-type", "location": %s, "size_expression": %s, "data_type": %s})",
                        location.to_string().c_str(),
                        size_expression->to_string().c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
