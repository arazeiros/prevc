#include <prevc/pipeline/AST/function-declaration.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        namespace AST
        {
            FunctionDeclaration::FunctionDeclaration(Pipeline* pipeline, util::Location&& location,
                                     const util::String& name, Type* type, AST::Parameters* parameters,
                                     Expression* implementation):
                Declaration(pipeline, std::move(location), Declaration::Kind::Function, name, type),
                parameters(parameters),
                implementation(implementation),
                frame(nullptr)
            {

            }

            FunctionDeclaration::~FunctionDeclaration()
            {
                delete parameters;

                if (implementation != nullptr)
                    delete implementation;

                if (frame != nullptr)
                    delete frame;
            }

            void FunctionDeclaration::check_semantics()
            {
                Declaration::check_semantics();

                auto& global_namespace = pipeline->global_namespace;
                pipeline->frame_system->push();
                global_namespace->push_scope();

                for (auto& parameter : *parameters)
                {
                    if (global_namespace->insert_declaration(parameter))
                        continue;

                    auto  duplicate = global_namespace->find_declaration(parameter->name).value();
                    auto& location  = duplicate->location;

                    CompileTimeError::raise(pipeline->file_name, parameter->location,
                            util::String::format("parameter name `%s` already used (at %d:%d)",
                                    parameter->name.c_str(), location.line_0, location.column_0));
                }

                parameters->check_semantics();

                for (auto& parameter : *parameters)
                {
                    const auto& parameter_type = parameter->get_semantic_type();

                    if (!parameter_type->can_be_passed())
                        CompileTimeError::raise(pipeline->file_name, parameter->location, util::String::format(
                                "functions parameters can only be of type `bool`, `char`, `int` or `ptr <anything>`, "
                                "type `%s` is not one of them", parameter_type->to_string().c_str()));
                }

                const auto& return_type = this->get_semantic_type();

                if (!return_type->can_be_returned())
                    CompileTimeError::raise(pipeline->file_name, type->location, util::String::format(
                            "functions return type can only be `void`, `bool`, `char`, `int` or `ptr <anything>`, "
                            "type `%s` is not one of them", return_type->to_string().c_str()));

                if (implementation != nullptr)
                {
                    implementation->check_semantics();
                    const auto& implementation_type = implementation->get_semantic_type();

                    if (!this->get_semantic_type()->equals(implementation->get_semantic_type()))
                        CompileTimeError::raise(pipeline->file_name, this->location, util::String::format(
                                "declared function `%s` return type is `%s`, but the provided implementation returns "
                                "an expression of type `%s`",
                                this->name.c_str(), this->get_semantic_type()->to_string().c_str(),
                                implementation_type->to_string().c_str()));
                }

                global_namespace->pop_scope();
                this->frame = (semantic_analysis::Frame*) pipeline->frame_system->pop();
            }

            util::String FunctionDeclaration::get_native_name() const
            {
                return (frame->level <= 1)
                    ? name
                    : util::String::format("f_%i_%zu", this->frame->level, this->id);
            }

            void FunctionDeclaration::generate_IR_declaration()
            {
                auto& module   = this->pipeline->IR_module;
                auto& context  = module->getContext();
                auto  sem_type = ((semantic_analysis::Type*) this->get_semantic_type());
                auto  type     = sem_type->get_llvm_type(context);
                auto  linkage  = (this->frame->level <= 1) ? llvm::Function::ExternalLinkage : llvm::Function::PrivateLinkage;
                llvm_parameters.reserve(parameters->size() + 1);

                if (this->frame->level > 1)
                    llvm_parameters.push_back(llvm::PointerType::getUnqual(frame->static_link->get_llvm_type(context)));

                for (auto& parameter : *this->parameters)
                    llvm_parameters.push_back(((semantic_analysis::Type*) parameter->get_semantic_type())->get_llvm_type(context));

                auto  fun_type = llvm::FunctionType::get(type, llvm_parameters, false);
                auto  function = llvm::Function::Create(fun_type, linkage, get_native_name().c_str(), module);
                function->setCallingConv(llvm::CallingConv::C);
            }

            void FunctionDeclaration::generate_IR_implementation()
            {
                if (this->implementation != nullptr)
                {
                    auto& module   = this->pipeline->IR_module;
                    auto& context  = module->getContext();
                    auto  sem_type = ((semantic_analysis::Type*) this->get_semantic_type());
                    auto  function = module->getFunction(get_native_name().c_str());

                    llvm::IRBuilder<> builder(llvm::BasicBlock::Create(context, "entry", function));
                    auto frame_type = this->frame->get_llvm_type(context);
                    auto allocated = builder.CreateAlloca(frame_type);
                    this->frame->allocated_frame = allocated;

                    if (this->frame->level > 1)
                    {
                        // copy the static link in the local variable
                        auto static_link = function->arg_begin();
                        auto var_SL      = builder.CreateStructGEP(frame_type, allocated, 0);
                        builder.CreateStore(static_link, var_SL);
                    }

                    auto value = this->implementation->generate_IR(&builder);

                    if (!sem_type->is_void())
                        builder.CreateRet(value);
                    else
                        builder.CreateRetVoid();
                }
            }

            util::String FunctionDeclaration::to_string() const noexcept
            {
                return util::String::format(
                        R"({"type": "function-declaration", "location": %s, "name": "%s", "declarationType": %s, "parameters": %s, "implementation": %s})",
                        location.to_string().c_str(),
                        name.c_str(),
                        type->to_string().c_str(),
                        parameters->to_string().c_str(),
                        implementation == nullptr
                            ? "null"
                            : implementation->to_string().c_str());
            }
        }
    }
}
