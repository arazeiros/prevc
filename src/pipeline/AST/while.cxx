#include <prevc/pipeline/AST/while.hxx>
#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            While::While(Pipeline* pipeline, util::Location&& location, Expression* condition, Statements* body):
                Statement(pipeline, std::move(location)),
                condition(condition),
                body(body)
            {

            }

            While::~While()
            {
                delete condition;
                delete body;
            }

            void While::check_semantics()
            {
                condition->check_semantics();
                body->check_semantics();

                const auto& condition_type = condition->get_semantic_type();

                if (!condition_type->is_bool())
                    CompileTimeError::raise(pipeline->file_name, condition->location, util::String::format(
                            "condition expressions of while-statements must be of type `bool`, "
                            "the given expression is of type `%s`",
                            condition_type->to_string().c_str()));
            }

            void While::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto& context   = builder->getContext();
                auto parent     = builder->GetInsertBlock()->getParent();
                auto test_block = llvm::BasicBlock::Create(context, "test", parent);
                auto do_block   = llvm::BasicBlock::Create(context, "do", parent);
                auto out_block  = llvm::BasicBlock::Create(context, "out", parent);

                builder->CreateBr(test_block);

                builder->SetInsertPoint(test_block);
                auto condition = builder->CreateICmpNE(this->condition->generate_IR(builder), builder->getInt8(0));
                builder->CreateCondBr(condition, do_block, out_block);

                builder->SetInsertPoint(do_block);
                this->body->generate_IR(builder);
                builder->CreateBr(test_block);

                builder->SetInsertPoint(out_block);
            }

            util::String While::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "while", "location": %s, "condition": %s, "body": %s})",
                        location.to_string().c_str(),
                        condition->to_string().c_str(),
                        body->to_string().c_str());
            }
        }
    }
}
