#include <prevc/pipeline/AST/array-type.hxx>
#include <prevc/pipeline/semantic_analysis/array-type.hxx>
#include <sstream>
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
                type(type),
                semantic_length(0)
            {

            }

            ArrayType::~ArrayType()
            {
                delete size_expression;
                delete type;
            }

            void ArrayType::check_semantics()
            {
                auto length_opt = size_expression->evaluate_as_integer();

                if (!length_opt.has_value())
                    CompileTimeError::raise(pipeline->file_name, location,
                            "array length must be evaluated at compile-time, the given expression "
                            "can not be evaluated at compile-time");

                auto length = (ptrdiff_t) length_opt.value();

                if (length < 0)
                    CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                            "invalid array length `%li`, can not be negative", length));

                semantic_length = (size_t) length;
                type->check_semantics();
            }

            util::String ArrayType::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "array-type", "location": %s, "size_expression": %s, "data_type": %s})",
                        location.to_string().c_str(),
                        size_expression->to_string().c_str(),
                        type->to_string().c_str());
            }

            util::String ArrayType::to_semantic_string() const noexcept
            {
                std::stringstream stream;
                stream << "arr [";
                stream << this->semantic_length;
                stream << "] ";
                stream << this->type->get_semantic_type()->id.c_str();
                return stream.str();
            }

            const semantic_analysis::Type* ArrayType::generate_semantic_type() const noexcept
            {
                return pipeline->type_system->get_or_insert(to_semantic_string(), [this] ()
                    {
                        return new semantic_analysis::ArrayType(this->type->get_semantic_type(), this->semantic_length);
                    });
            }
        }
    }
}
