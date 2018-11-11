#include <prevc/pipeline/AST/cast.hxx>
#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
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

            void Cast::check_semantics()
            {
                type->check_semantics();
                sub->check_semantics();

                auto cast_type = type->get_semantic_type();
                auto expression_type = sub->get_semantic_type();

                if (!cast_type->is_void())
                {
                    if (cast_type->is_int())
                    {
                        if (!expression_type->is_int() &&
                            !expression_type->is_char() &&
                            !expression_type->is_bool())
                            CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                                    "casting to type `int` is allowed only to expressions of type `int`, `char` or `bool`, "
                                    "but given expression is of type `%s`", expression_type->to_string().c_str()));
                    }
                    else if (cast_type->is_pointer())
                    {
                        if (!expression_type->is_pointer()
                            || !expression_type->as_pointer()->sub->is_void())
                            CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                                    "casting to type `%s` is allowed only to expressions of type `ptr void`",
                                    cast_type->to_string().c_str()));
                    }
                    else
                    {
                        CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                                "casting to type `%s` is not allowed",
                                cast_type->to_string().c_str()));
                    }
                }
            }

            llvm::Value* Cast::generate_IR(llvm::IRBuilder<> *builder)
            {
                return sub->generate_IR(builder);
            }

            std::optional<int64_t> Cast::evaluate_as_integer() const noexcept
            {
                return sub->evaluate_as_integer();
            }

            const semantic_analysis::Type* Cast::get_semantic_type()
            {
                return type->get_semantic_type();
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
