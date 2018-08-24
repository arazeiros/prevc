#include <prevc/pipeline/output_generation/output-generation.hxx>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/Target/TargetMachine.h>
#include <prevc/pipeline/AST/expression.hxx>

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

                auto f_malloc    = (llvm::Function*) module->getOrInsertFunction("malloc", ptrType, intType, nullptr);
                auto f_free      = (llvm::Function*) module->getOrInsertFunction("free", voidType, ptrType, nullptr);
                auto f_printf    = (llvm::Function*) module->getOrInsertFunction("printf", llvm::FunctionType::get(int32Type, {ptrType}, true));
                auto f_putchar   = (llvm::Function*) module->getOrInsertFunction("putchar", llvm::FunctionType::get(int32Type, {int32Type}, false));
                auto f_printint  = llvm::Function::Create(llvm::FunctionType::get(voidType, {intType}, false), llvm::Function::PrivateLinkage, "printint", module);
                auto f_printchar = llvm::Function::Create(llvm::FunctionType::get(voidType, {intType}, false), llvm::Function::PrivateLinkage, "printchar", module);
                auto f_println   = llvm::Function::Create(llvm::FunctionType::get(voidType, false), llvm::Function::PrivateLinkage, "println", module);

                {
                    // defining printint
                    auto arg0 = f_printint->arg_begin();
                    auto block = llvm::BasicBlock::Create(*context, "printint_entry", f_printint);
                    llvm::IRBuilder<> builder(block);
                    builder.CreateCall(f_printf, llvm::ArrayRef<llvm::Value*>({builder.CreateGlobalStringPtr("%ld"), arg0}));
                    builder.CreateRetVoid();
                }

                {
                    // defining printchar
                    auto arg0 = f_printchar->arg_begin();
                    auto block = llvm::BasicBlock::Create(*context, "printchar_entry", f_printchar);
                    llvm::IRBuilder<> builder(block);
                    builder.CreateCall(f_putchar, llvm::ArrayRef<llvm::Value*>({arg0}));
                    builder.CreateRetVoid();
                }

                {
                    // defining println
                    auto block = llvm::BasicBlock::Create(*context, "println_entry", f_println);
                    llvm::IRBuilder<> builder(block);
                    llvm::ArrayRef<llvm::Value*> args({llvm::ConstantInt::get(int32Type, '\n')});
                    builder.CreateCall(f_putchar, args);
                    builder.CreateRetVoid();
                }
            }

            void OutputGeneration::complete_0()
            {
                auto context = new llvm::LLVMContext();
                auto module = new llvm::Module(pipeline->file_name, *context);
                pipeline->IR_module = module;

                auto target_triple = llvm::sys::getDefaultTargetTriple();
                std::string error;
                auto target = llvm::TargetRegistry::lookupTarget(target_triple, error);

                if (target == nullptr)
                {
                    InternalError::raise(error.c_str());
                    return; // should never come here, but disable warnings
                }

                auto RM = llvm::Optional<llvm::Reloc::Model>();
                auto target_machine = target->createTargetMachine(target_triple, "generic", "", llvm::TargetOptions(), RM);
                module->setDataLayout(target_machine->createDataLayout());
                module->setTargetTriple(target_triple);

                declare_standard_library(context, module);

                auto main_type = llvm::Type::getInt32Ty(*context);
                auto main = (llvm::Function*) module->getOrInsertFunction("main", main_type, NULL);
                main->setCallingConv(llvm::CallingConv::C);
                auto block = llvm::BasicBlock::Create(*context, "entry", main);
                llvm::IRBuilder<> builder(block);
                auto expression = ((AST::Expression *) pipeline->abstract_syntax_tree)->generate_IR(&builder);
                builder.CreateRet(builder.CreateIntCast(expression, main_type, true));

                const std::size_t extension_length = std::string(".prev").length();
                const std::string exe_name = pipeline->file_name.substr(0, pipeline->file_name.length() - extension_length);
                const std::string obj_name = exe_name + ".o";

                std::error_code error_code;
                llvm::raw_fd_ostream out(obj_name, error_code, llvm::sys::fs::OpenFlags::F_None);

                if (error_code)
                    IOError::raise(util::String::format("could not open file: %s", error_code.message().c_str()));

                llvm::legacy::PassManager pass_manager;

                if (target_machine->addPassesToEmitFile(pass_manager, out, llvm::TargetMachine::CGFT_ObjectFile))
                    InternalError::raise("target_machine can't emit a file of this type");

                pass_manager.run(*module);
                out.flush();

                pipeline->release_abstract_syntax_tree();

                util::String link_command(util::String::format("clang -o %s %s", exe_name.c_str(), obj_name.c_str()));
                std::system(link_command.c_str());
            }
        }
    }
}
