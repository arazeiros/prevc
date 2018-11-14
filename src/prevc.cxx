#include <algorithm>
#include <clocale>
#include <cstring>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <prevc/error.hxx>
#include <prevc/settings.hxx>
#include <prevc/pipeline/pipeline.hxx>

using namespace prevc;

int main(int argc, char** argv)
{
    try
    {
        auto settings = Settings::parse(argc, argv);

        if (settings->help)
            print_help();
        else if (settings->version)
            print_version();
        else
        {
            setlocale(LC_ALL, "");
            LLVMInitializeX86TargetInfo();
            LLVMInitializeX86Target();
            LLVMInitializeX86TargetMC();
            LLVMInitializeX86AsmPrinter();

            for (auto source : settings->sources)
            {
                pipeline::Pipeline* pipeline = new pipeline::Pipeline(settings, source);
                pipeline->compile();
                delete pipeline;
            }

            llvm::llvm_shutdown();
        }

        delete settings;
    }
    catch (ArgumentsError& error)
    {
        error.log();
        return 1;
    }
    catch (CompileTimeError& error)
    {
        error.log();
        return 2;
    }
    catch (Error& error)
    {
        error.log(stderr);
        return 3;
    }

    return 0;
}
