#include <prevc/pipeline/output_generation/output-generation.hxx>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <prevc/pipeline/AST/expression.hxx>
#include <prevc/pipeline/AST/variable-declaration.hxx>
#include <prevc/settings.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace output_generation
        {
            OutputGeneration::OutputGeneration(Pipeline* pipeline):
                Phase(pipeline)
            {

            }

            OutputGeneration::~OutputGeneration() = default;

            static void declare_standard_library(llvm::LLVMContext* context, llvm::Module* module)
            {
                auto voidType  = llvm::Type::getVoidTy(*context);
                auto int32Type = llvm::Type::getInt32Ty(*context);
                auto intType   = llvm::Type::getInt64Ty(*context);
                auto ptrType   = llvm::Type::getInt8PtrTy(*context);

                auto f_malloc    = module->getOrInsertFunction("malloc", llvm::FunctionType::get(ptrType, {intType}, false));
                auto f_free      = module->getOrInsertFunction("free", llvm::FunctionType::get(voidType, {ptrType}, false));
                auto f_printf    = module->getOrInsertFunction("printf", llvm::FunctionType::get(int32Type, {ptrType}, true));
                auto f_putchar   = module->getOrInsertFunction("putchar", llvm::FunctionType::get(int32Type, {int32Type}, false));
                auto f_printint  = llvm::Function::Create(llvm::FunctionType::get(voidType, {intType}, false), llvm::Function::PrivateLinkage, "printint", module);
                auto f_printchar = llvm::Function::Create(llvm::FunctionType::get(voidType, {intType}, false), llvm::Function::PrivateLinkage, "printchar", module);
                auto f_printbool = llvm::Function::Create(llvm::FunctionType::get(voidType, {intType}, false), llvm::Function::PrivateLinkage, "printbool", module);
                auto f_println   = llvm::Function::Create(llvm::FunctionType::get(voidType, false), llvm::Function::PrivateLinkage, "println", module);

                {
                    // defining printint
                    auto arg0 = f_printint->arg_begin();
                    auto block = llvm::BasicBlock::Create(*context, "entry", f_printint);
                    llvm::IRBuilder<> builder(block);
                    builder.CreateCall(f_printf, llvm::ArrayRef<llvm::Value*>({builder.CreateGlobalStringPtr("%ld"), arg0}));
                    builder.CreateRetVoid();
                }

                {
                    // defining printchar
                    auto arg0 = f_printchar->arg_begin();
                    auto block = llvm::BasicBlock::Create(*context, "entry", f_printchar);
                    llvm::IRBuilder<> builder(block);
                    builder.CreateCall(f_putchar, llvm::ArrayRef<llvm::Value*>({arg0}));
                    builder.CreateRetVoid();
                }

                {
                    // defining printbool
                    auto arg0        = f_printbool->arg_begin();
                    auto entry       = llvm::BasicBlock::Create(*context, "entry", f_printbool);
                    auto print_true  = llvm::BasicBlock::Create(*context, "is_true", f_printbool);
                    auto print_false = llvm::BasicBlock::Create(*context, "is_false");
                    auto get_out     = llvm::BasicBlock::Create(*context, "get_out");

                    llvm::IRBuilder<> builder(entry);
                    auto result = builder.CreateICmpNE(arg0, llvm::ConstantInt::get(intType, 0));
                    builder.CreateCondBr(result, print_true, print_false);

                    builder.SetInsertPoint(print_true);
                    auto str_true = builder.CreateGlobalStringPtr("true");
                    builder.CreateBr(get_out);
                    print_true = builder.GetInsertBlock();

                    f_printbool->getBasicBlockList().push_back(print_false);
                    builder.SetInsertPoint(print_false);
                    auto str_false = builder.CreateGlobalStringPtr("false");
                    builder.CreateBr(get_out);
                    print_false = builder.GetInsertBlock();

                    f_printbool->getBasicBlockList().push_back(get_out);
                    builder.SetInsertPoint(get_out);
                    auto phi = builder.CreatePHI(ptrType, 2);
                    phi->addIncoming(str_true, print_true);
                    phi->addIncoming(str_false, print_false);
                    auto str_formatted_str = builder.CreateGlobalStringPtr("%s");
                    builder.CreateCall(f_printf, llvm::ArrayRef<llvm::Value*>({str_formatted_str, phi}));
                    builder.CreateRetVoid();
                }

                {
                    // defining println
                    auto block = llvm::BasicBlock::Create(*context, "entry", f_println);
                    llvm::IRBuilder<> builder(block);
                    builder.CreateCall(f_putchar, llvm::ArrayRef<llvm::Value*>({llvm::ConstantInt::get(int32Type, '\n')}));
                    builder.CreateRetVoid();
                }
            }

            static llvm::TargetMachine* generate_code(llvm::LLVMContext* context, llvm::Module* module, Pipeline* pipeline)
            {
                auto target_triple = llvm::sys::getDefaultTargetTriple();
                std::string error;
                auto target = llvm::TargetRegistry::lookupTarget(target_triple, error);

                if (target == nullptr)
                {
                    InternalError::raise(error.c_str());
                    return nullptr; // should never come here, but disable warnings
                }

                auto RM = llvm::Optional<llvm::Reloc::Model>(llvm::Reloc::Model::PIC_);
                auto target_machine = target->createTargetMachine(target_triple, "generic", "", llvm::TargetOptions(), RM);
                module->setDataLayout(target_machine->createDataLayout());
                module->setTargetTriple(target_triple);

                declare_standard_library(context, module);

                for (auto variable : pipeline->global_variables)
                {
                    auto name = variable->name.c_str();
                    auto type = ((semantic_analysis::Type*) variable->get_semantic_type())->get_llvm_type(*context);

                    auto global_variable = new llvm::GlobalVariable(*module, type, false,
                                                                    llvm::GlobalValue::InternalLinkage, nullptr, name);

                    global_variable->setInitializer(llvm::ConstantInt::getFalse(*context));
                }

                auto main_type = llvm::Type::getInt32Ty(*context);
                module->getOrInsertFunction("main", main_type);
                auto main = module->getFunction("main");
                main->setCallingConv(llvm::CallingConv::C);
                auto block = llvm::BasicBlock::Create(*context, "entry", main);
                llvm::IRBuilder<> builder(block);
                auto expression = ((AST::Expression *) pipeline->abstract_syntax_tree)->generate_IR(&builder);
                builder.CreateRet(builder.CreateIntCast(expression, main_type, true));
                return target_machine;
            }

            static void emit_code(llvm::Module* module, llvm::TargetMachine* target_machine, Pipeline* pipeline)
            {
                const std::size_t extension_length = std::string(".prev").length();
                const std::string base_name = pipeline->file_name.substr(0, pipeline->file_name.length() - extension_length);

                switch (pipeline->settings->output_format)
                {
                    case Settings::OutputFormat::EXECUTABLE:
                    {
                        const std::string obj_name = base_name + ".o";

                        std::error_code error_code;
                        llvm::raw_fd_ostream out(obj_name, error_code, llvm::sys::fs::OpenFlags::OF_None);

                        if (error_code)
                            IOError::raise(util::String::format("could not open file: %s", error_code.message().c_str()));

                        llvm::legacy::PassManager pass_manager;

                        if (target_machine->addPassesToEmitFile(pass_manager, out, nullptr, llvm::CGFT_ObjectFile))
                            InternalError::raise("target_machine can't emit a file of this type");

                        pass_manager.run(*module);
                        out.flush();

                        pipeline->release_abstract_syntax_tree();

                        std::stringstream link_command;
                        link_command << "ld -pie -z relro --hash-style=gnu --build-id --eh-frame-hdr -m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 -o ";
                        link_command << base_name.c_str() << " /lib/x86_64-linux-gnu/Scrt1.o /lib/x86_64-linux-gnu/crti.o ";
                        link_command << obj_name.c_str() << " -lc /lib/x86_64-linux-gnu/crtn.o";

                        std::system(link_command.str().c_str());
                        break;
                    }

                    case Settings::OutputFormat::LLVM_IR:
                    {
                        const std::string llvm_ir_name = base_name + ".ll";

                        std::error_code error_code;
                        llvm::raw_fd_ostream out(llvm_ir_name, error_code, llvm::sys::fs::OpenFlags::OF_Text);

                        if (error_code)
                            IOError::raise(util::String::format("could not open file: %s", error_code.message().c_str()));

                        module->print(out, nullptr);
                    }
                }
            }

            void OutputGeneration::complete_0()
            {
                auto context = new llvm::LLVMContext();
                auto module = new llvm::Module(pipeline->file_name, *context);
                pipeline->IR_module = module;

                auto target_machine = generate_code(context, module, pipeline);
                emit_code(module, target_machine, pipeline);
            }
        }
    }
}
