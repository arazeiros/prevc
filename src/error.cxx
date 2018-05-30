#include <prevc/error.hxx>
#include <sstream>
#include <utility>

namespace prevc
{
    static util::String build_compile_time_error_message(const util::String& reference, const util::Location& location,
        const util::String& message, bool error)
    {
        std::ostringstream buffer;
        buffer << (error ? "ERROR" : "WARNING");
        buffer << " ";
        buffer << reference.c_str();
        buffer << ":";
        buffer << location.line_0;
        buffer << ":";
        buffer << location.column_0;
        buffer << " ";
        buffer << message.c_str();
        return buffer.str();
    }

    static util::String build_simple_error_message(const util::String& type, const util::String& message)
    {
        std::ostringstream buffer;
        buffer << type.c_str();
        buffer << ": ";
        buffer << message.c_str();
        return buffer.str();
    }

    Error::Error(util::String&& message):
        message(std::move(message))
    {

    }

    const char* Error::what() const throw()
    {
        return message.c_str();
    }

    void Error::log(FILE *out)
    {
        fputs(what(), out);
        fputc('\n', out);
    }

    IOError::IOError(util::String&& message):
        Error(std::move(message))
    {

    }

    void IOError::raise(const util::String &message)
    {
        throw IOError(build_simple_error_message("IO ERROR", message));
    }

    CompileTimeError::CompileTimeError(util::String&& message):
        Error(std::move(message))
    {

    }

    void CompileTimeError::raise(const util::String& reference, const util::Location& location,
        const util::String& message)
    {
        throw CompileTimeError(build_compile_time_error_message(reference, location, message, true));
    }

    InternalError::InternalError(util::String&& message):
        Error(std::move(message))
    {

    }

    void InternalError::raise(const util::String& message)
    {
        throw InternalError(build_simple_error_message("INTERNAL ERROR", message));
    }

    ArgumentsError::ArgumentsError(util::String&& message):
        Error(std::move(message))
    {

    }

    void ArgumentsError::raise(const util::String& message)
    {
        throw ArgumentsError(build_simple_error_message("ARGUMENTS ERROR", message));
    }
}
