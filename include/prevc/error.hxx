
#ifndef PREVC_ERROR_HXX
#define PREVC_ERROR_HXX

#include <cstdio>
#include <exception>
#include <prevc/util/location.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    /**
     * \brief A general error class.
     * */
    class Error: public std::exception
    {
    public:
        /**
         * \brief The error message.
         * */
        const util::String message;

        /**
         * \brief Returns the error message in C-string form.
         * \return The error message in C-string form.
         * */
        virtual const char* what() const throw();

        /**
         * \brief Log the error message to the specified output stream.
         * \param out The specified output stream.
         * */
        void log(FILE* out = stdout);

    protected:
        /**
         * \brief Create an error with the specified message.
         * \param message The error message.
         * */
        Error(util::String&& message);
    };

    /**
     * \brief A class for IO errors.
     * */
    class IOError: public Error
    {
    public:
        /**
         * \brief Raise an IO error with the specified message.
         * \param message The error message.
         * */
        static void raise(const util::String& message);

    private:
        /**
         * \brief Create an IO error with the specified message.
         * \param message The error message.
         * */
        IOError(util::String&& message);
    };

    /**
     * \brief A class for compile-time errors.
     * */
    class CompileTimeError: public Error
    {
    public:
        /**
         * \brief Raise an internal error with the specified
         * \param reference The source file that has the error.
         * \param location The location of error in the source file.
         * \param message The error message.
         * */
        [[noreturn]] static void raise(const util::String& reference, const util::Location& location, const util::String& message);

    private:
        /**
         * \brief Create a compile time error with the specified message.
         * \param message The error message.
         * */
        CompileTimeError(util::String&& message);
    };

    /**
     * \brief A class for internal errors.
     * */
    class InternalError: public Error
    {
    public:
        /**
         * \brief Raise an internal error with the specified
         * \param message The error message.
         * */
        [[noreturn]] static void raise(const util::String& message);

    private:
        /**
         * \brief Create an internal error with the specified message.
         * \param message The error message.
         * */
        InternalError(util::String&& message);
    };

    /**
     * \brief A class arguments errors.
     * */
    class ArgumentsError: public Error
    {
    public:
        /**
         * \brief Raise an internal error with the specified message.
         * \param message The error message.
         * */
        [[noreturn]] static void raise(const util::String& message);

    private:
        /**
         * \brief Create an internal error with the specified message.
         * \param message The error message.
         * */
        ArgumentsError(util::String&& message);
    };
}

#endif
