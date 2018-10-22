#include <prevc/pipeline/AST/array-access.hxx>
#include <utility>
#include <prevc/error.hxx>

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

                // TODO check that array is of type array
                // TODO check that index is of type int
            }

            llvm::Value* ArrayAccess::generate_IR(llvm::IRBuilder<>* builder)
            {
                // TODO implement
                InternalError::raise("missing implementation: AST array access generating IR");
                return nullptr;
            }

            std::optional<int64_t> ArrayAccess::evaluate_as_integer() const noexcept
            {
                return {};
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
