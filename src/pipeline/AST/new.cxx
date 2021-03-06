#include <prevc/pipeline/AST/new.hxx>
#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
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

            void New::check_semantics()
            {
                type->check_semantics();

                if (type->get_semantic_type()->is_void())
                    CompileTimeError::raise(pipeline->file_name, location,
                            "memory allocations of type `void` are not allowed");
            }

            llvm::Value* New::generate_IR(llvm::IRBuilder<> *builder)
            {
                auto& module  = pipeline->IR_module;
                auto& context = module->getContext();
                llvm::DataLayout layout(module);

                auto type = ((semantic_analysis::Type*) this->type->get_semantic_type())->get_llvm_type(context);
                auto size = builder->getInt64(layout.getTypeStoreSize(type));

                auto f_malloc = module->getFunction("malloc");
                auto result = builder->CreateCall(f_malloc, llvm::ArrayRef<llvm::Value*>({size}));
                return builder->CreatePointerCast(result, llvm::PointerType::getUnqual(type));
            }

            std::optional<int64_t> New::evaluate_as_integer() const noexcept
            {
                return {};
            }

            const semantic_analysis::Type* New::get_semantic_type()
            {
                static const util::String s_ptr = "ptr ";
                auto semantic_type = type->get_semantic_type();

                return pipeline->type_system->get_or_insert(s_ptr + semantic_type->get_id(), [semantic_type] ()
                    {
                        return new semantic_analysis::PointerType(semantic_type);
                    });
            }

            util::String New::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "new", "location": %s, "dataType": %s})",
                        location.to_string().c_str(),
                        type->to_string().c_str());
            }
        }
    }
}
