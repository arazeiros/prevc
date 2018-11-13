#include <prevc/settings.hxx>
#include <prevc/error.hxx>
#include <prevc/version.hxx>
#include <cstring>
#include <cstdio>

namespace prevc
{
    Settings::Settings():
        help(false),
        version(false),
        output_format(OutputFormat::EXECUTABLE)
    {

    }

    static const char* match(const char* s, const char* prefix)
    {
        size_t len = std::strlen(prefix);

        return (std::strncmp(prefix, s, len) == 0)
            ? &s[len]
            : nullptr;
    }

    static void unknown_argument(const char* arg)
    {
        ArgumentsError::raise(util::String::format(
                "unknown command line argument `%s`", arg));
    }

    static void assert_prev_extension(const char* source)
    {
        const char* dot = strrchr(source, '.');

        if (dot != nullptr)
            if (strcmp(dot, ".prev") == 0)
                return;

        ArgumentsError::raise(util::String::format(
                "specified source `%s` has not the `.prev` extension", source));
    }

    static void assert_no_ext(const char* ext, const char* arg)
    {
        if (ext[0] != '\0')
            unknown_argument(arg);
    }

    const Settings* Settings::parse(int argc, const char* const* argv)
    {
        auto settings = new Settings();

        for (int i = 1; i < argc; ++i)
        {
            const char* arg = argv[i];
            const char* option = nullptr;

            if ((option = match(arg, "--")))
            {
                const char* ext = nullptr;

                if ((ext = match(option, "help")))
                {
                    assert_no_ext(ext, arg);
                    settings->help = true;
                }
                else if ((ext = match(option, "version")))
                {
                    assert_no_ext(ext, arg);
                    settings->version = true;
                }
                else if ((ext = match(option, "out-llvm-ir")))
                {
                    assert_no_ext(ext, arg);
                    settings->output_format = Settings::OutputFormat::LLVM_IR;
                }
                else
                {
                    unknown_argument(arg);
                }
            }
            else if ((option = match(arg, "-")))
            {
                unknown_argument(arg);
            }
            else
            {
                assert_prev_extension(arg);
                settings->sources.push_back(arg);
            }
        }

        return settings;
    }

    void print_help()
    {
        printf(
                "Usage: prevc [OPTIONS] SOURCE...\n"
                "\n"
                "Options:\n"
                "    --out-llvm-ir    Produces llvm IR as compilation output.\n"
                "    --version        Prints compiler version.\n"
                "    --help           Prints this help.\n"
        );
    }

    void print_version()
    {
        printf("prevc v%i.%i.%i\n",
                PREVC_VERSION_MAJOR,
                PREVC_VERSION_MINOR,
                PREVC_VERSION_BUILD);
    }
}
