
#ifndef PREVC_SETTINGS_HXX
#define PREVC_SETTINGS_HXX

#include <vector>

namespace prevc
{
    struct Settings
    {
        /**
         * \brief Enumeration of possible output formats.
         * */
        enum class OutputFormat
        {
            EXECUTABLE,
            LLVM_IR
        };

        bool                        help;
        bool                        version;
        std::vector<const char*>    sources;
        OutputFormat                output_format;

    private:
        /**
         * \brief Construct the default settings.
         * */
        Settings();

    public:
        /**
         * \brief Default implementation.
         * */
        ~Settings() = default;

        /**
         * \brief Parse settings from the command line arguments.
         * \return The settings (should be `delete`d).
         * */
        static const Settings* parse(int argc, const char* const* argv);
    };

    /**
     * \brief Prints help.
     * */
    void print_help();

    /**
     * \brief Prints compiler version.
     * */
    void print_version();
}

#endif
