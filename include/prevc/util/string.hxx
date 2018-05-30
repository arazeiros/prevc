
#ifndef PREVC_UTIL_STRING_HXX
#define PREVC_UTIL_STRING_HXX

#include <cstdint>
#include <string>
#include <vector>

namespace prevc
{
    namespace util
    {
        /**
         * \brief An immutable UTF-8 string.
         * */
        class String
        {
        public:
            /**
             * \brief The capacity of the internal buffer of bytes used for this string representation.
             * */
            const std::size_t capacity;

            /**
             * \brief The move constructor.
             * \param other The other object.
             * */
            String(String&& other) noexcept;

            /**
             * \brief The copy constructor.
             * \param other The other object.
             * */
            String(const String& other) noexcept;

            /**
             * \brief Create an empty string.
             */
            String() noexcept;

            /**
             * \brief Create a string copying a specified amount of data expressed in bytes from a specified memory
             *     address.
             * \param data The specified memory address from which data is copied.
             * \param bytes_to_copy The specified amount of data to copy expressed in bytes.
             *
             * Note that data shouldn't contains the null-terminating character, since this will be always added by
             * this constructor. Safety it's important, dude.
             */
            String(const std::uint8_t* data, std::size_t bytes_to_copy);

            /**
             * \brief Create a string copying data from specified C-string.
             * \param str The specified C-string. If nullptr then an empty string will be created.
             * */
            String(const char* str);

            /**
             * \brief Create a string copying data from specified std::string object.
             * \param str The specified std::string object.
             * */
            String(const std::string& str);

            /**
             * \brief Create a string using the bytes in a specified vector.
             * \param vector The specified vector
             * */
            String(const std::vector<std::uint8_t>& vector);

            /**
             * \brief Free the used memory resources (if any).
             * */
            ~String();

            /**
             * \brief Returns a pointer to an array that contains a null-terminated sequence of characters
             *     (i.e., a C-string) representing the current value of the string object.
             * \return The pointer to the C-string.
             * */
            const char* c_str() const noexcept;

            /**
             * \brief Tells if the string is empty.
             * \return True if empty, false otherwise.
             *
             * A string is empty if contains no characters (except null-terminating character).
             * */
            bool is_empty() const noexcept;

            /**
             * \brief Tells if this string is equal to the specified one.
             * \param other The string to compare with.
             * \return True if strings equals, false otherwise.
             * */
            bool operator==(const String& other) const noexcept;

            /**
             * \brief Create a String out of the C-like formatted one.
             * \param format The formatted C-like string.
             * \param ... The format arguments.
             * */
            static String format(const char* format, ...);

        private:
            /**
             * \brief The internal buffer that stores data.
             * */
            const std::uint8_t* buffer;
        };
    }
}

#endif
