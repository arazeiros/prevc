#include <prevc/util/string.hxx>
#include <algorithm>
#include <cstdarg>
#include <cstring>

namespace prevc
{
    namespace util
    {
        static const std::uint8_t* const EMPTY_STRING = (std::uint8_t*) "";

        String::String(String&& other) noexcept:
            capacity(other.capacity),
            buffer(other.buffer)
        {
            other.buffer = nullptr;
        }

        String::String(const String& other) noexcept:
            String(other.buffer, other.capacity - 1)
        {

        }

        String::String() noexcept:
            capacity(1),
            buffer(EMPTY_STRING)
        {

        }

        String::String(const std::uint8_t* data, std::size_t bytes_to_copy, bool move_ownership):
            capacity(bytes_to_copy + 1),
            buffer([&] () -> const std::uint8_t*
                {
                    if (capacity == 1)
                        return EMPTY_STRING;

                    if (move_ownership)
                        return data;

                    auto tmp = new std::uint8_t[capacity];
                    std::memcpy(tmp, data, bytes_to_copy);
                    tmp[bytes_to_copy] = '\0';
                    return tmp;
                } ())
        {

        }

        String::String(const char* str):
            String(str ? (const std::uint8_t*) str : EMPTY_STRING, str ? std::strlen(str) : 0)
        {

        }

        String::String(const std::string& str):
            String(str.c_str())
        {

        }

        String::String(const std::vector<std::uint8_t>& vector):
            String(vector.data(), vector.size())
        {

        }

        String::~String()
        {
            if (buffer != nullptr && !is_empty())
                delete[] buffer;
        }

        const char* String::c_str() const noexcept
        {
            return (const char*) buffer;
        }

        bool String::is_empty() const noexcept
        {
            return buffer == EMPTY_STRING;
        }

        String String::operator+(const String& other) const noexcept
        {
            const size_t this_length  = this->capacity - 1;
            const size_t other_length = other.capacity - 1;
            const size_t size         = this_length + other_length;

            auto buffer = new uint8_t[size + 1];

            std::memcpy(&buffer[0],           this->buffer, this_length );
            std::memcpy(&buffer[this_length], other.buffer, other_length);
            buffer[size] = 0;

            return String(buffer, size, true);
        }

        bool String::operator==(const String& other) const noexcept
        {
            return std::strcmp(this->c_str(), other.c_str()) == 0;
        }

        bool String::operator<(const String& other) const noexcept
        {
            return std::strcmp(this->c_str(), other.c_str()) < 0;
        }

        bool String::starts_with(const String& other) const noexcept
        {
            const auto& prefix = other.c_str();
            return strncmp(prefix, c_str(), strlen(prefix)) == 0;
        }

        String String::format(const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            char* buffer;
            vasprintf(&buffer, format, args);
            va_end(args);
            String tmp(buffer);
            std::free(buffer);
            return std::move(tmp);
        }
    }
}
