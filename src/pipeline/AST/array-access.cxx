#include <prevc/pipeline/AST/array-access.hxx>
#include <utility>
#include <prevc/error.hxx>
#include <prevc/pipeline/semantic_analysis/array-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            ArrayAccess::ArrayAccess(Pipeline* pipeline, util::Location&& location, Expression* array, Expression* index):
                Expression(pipeline, std::move(location)),
                array(array),
                index(index)
            {

            }

            ArrayAccess::~ArrayAccess()
            {
                delete array;
                delete index;
            }

            void ArrayAccess::check_semantics()
            {
                array->check_semantics();
                index->check_semantics();

                if (!array->get_semantic_type()->is_array())
                    CompileTimeError::raise(pipeline->file_name, location,
                            "trying to perform an array access, but the given expression is not an array");

                auto index_type = index->get_semantic_type();

                if (!index_type->is_int())
                    CompileTimeError::raise(pipeline->file_name, location, util::String::format(
                            "trying to perform an array access, the index expression must be of type `int`, "
                            "but is of type `%s`", index_type->to_string().c_str()));
            }

            llvm::Value* ArrayAccess::generate_IR(llvm::IRBuilder<>* builder)
            {
                return builder->CreateLoad(generate_IR_address(builder));
            }

            std::optional<int64_t> ArrayAccess::evaluate_as_integer() const noexcept
            {
                return {};
            }

            bool ArrayAccess::is_lvalue() const noexcept
            {
                return array->is_lvalue();
            }

            llvm::Value* ArrayAccess::generate_IR_address(llvm::IRBuilder<> *builder)
            {
                auto array = this->array->generate_IR_address(builder);
                auto index = this->index->generate_IR(builder);
                auto zero  = builder->getInt8(0);
                return builder->CreateGEP(array, {zero, index});
            }

            const semantic_analysis::Type* ArrayAccess::get_semantic_type()
            {
                return array->get_semantic_type()->as_array()->sub;
            }

            util::String ArrayAccess::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "array-access", "location": %s, "array": %s, "index": %s})",
                        location.to_string().c_str(),
                        array->to_string().c_str(),
                        index->to_string().c_str());
            }
        }
    }
}
