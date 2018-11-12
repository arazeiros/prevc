#include <prevc/pipeline/AST/if.hxx>
#include <prevc/pipeline/semantic_analysis/concrete-type.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            If::If(Pipeline* pipeline, util::Location&& location, Expression* condition,
                    Statements* then_body, Statements* else_body):
                Statement(pipeline, std::move(location)),
                condition(condition),
                then_body(then_body),
                else_body(else_body)
            {

            }

            If::~If()
            {
                delete condition;
                delete then_body;

                if (else_body != nullptr)
                    delete else_body;
            }

            void If::check_semantics()
            {
                condition->check_semantics();
                then_body->check_semantics();

                if (else_body != nullptr)
                    else_body->check_semantics();

                const auto& condition_type = condition->get_semantic_type();

                if (!condition_type->is_bool())
                    CompileTimeError::raise(pipeline->file_name, condition->location, util::String::format(
                            "condition expressions of if-statements must be of type `bool`, "
                            "the given expression is of type `%s`",
                            condition_type->to_string().c_str()));
            }

            void If::generate_IR(llvm::IRBuilder<>* builder)
            {
                auto& context   = builder->getContext();

                auto parent     = builder->GetInsertBlock()->getParent();
                auto then_block = llvm::BasicBlock::Create(context, "then", parent);
                auto else_block = llvm::BasicBlock::Create(context, "else");
                auto out_block  = llvm::BasicBlock::Create(context, "out");

                auto condition  = this->condition->generate_IR(builder);
                auto result     = builder->CreateICmpNE(condition, builder->getFalse());
                builder->CreateCondBr(result, then_block, else_block);

                builder->SetInsertPoint(then_block);
                then_body->generate_IR(builder);
                builder->CreateBr(out_block);
                // then_block = builder->GetInsertBlock();

                parent->getBasicBlockList().push_back(else_block);
                builder->SetInsertPoint(else_block);
                if (else_body != nullptr) else_body->generate_IR(builder);
                builder->CreateBr(out_block);
                // else_block = builder->GetInsertBlock();

                parent->getBasicBlockList().push_back(out_block);
                builder->SetInsertPoint(out_block);
                // out_block = builder->GetInsertBlock();
            }

            util::String If::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "if", "location": %s, "condition": %s, "then_body": %s, "else_body": %s})",
                        location.to_string().c_str(),
                        condition->to_string().c_str(),
                        then_body->to_string().c_str(),
                        else_body == nullptr
                            ? "null"
                            : else_body->to_string().c_str());
            }
        }
    }
}
