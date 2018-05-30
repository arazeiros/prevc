#include <algorithm>
#include <clocale>
#include <cstring>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <prevc/error.hxx>
#include <prevc/pipeline/pipeline.hxx>

using namespace prevc;

static void check_prev_extension(const char* file_name)
{
    const char* dot = strrchr(file_name, '.');

    if (dot != nullptr)
        if (strcmp(dot, ".prev") == 0)
            return;

    ArgumentsError::raise(util::String::format(R"(specified source file "%s" has not the ".prev" extension)", file_name));
}

int main(int argc, char** argv)
{
    try
    {
        setlocale(LC_ALL, "");
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmPrinters();

        for (int arg = 1; arg < argc; ++arg)
        {
            const char* file_name = argv[arg];
            check_prev_extension(file_name);
            pipeline::Pipeline* pipeline = new pipeline::Pipeline(file_name);
            pipeline->compile();
            delete pipeline;
        }

        llvm::llvm_shutdown();
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
