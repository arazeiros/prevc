

#ifndef PREVC_UTIL_READER_HXX
#define PREVC_UTIL_READER_HXX

#include <cstdint>
#include <cstdio>
#include <utility>
#include <prevc/util/string.hxx>

#define PREVC_UTIL_READER_DEFAULT_BUFFER_SIZE (8)

namespace prevc
{
    namespace util
    {
        /**
         * \brief A buffered reader that read UTF-8 input streams.
         * */
        class Reader
        {
        public:

            /**
             * \brief The END_OF_FILE value returned by method read_one().
             * */
            static const std::uint32_t END_OF_FILE = UINT32_MAX;

            /**
             * \brief reference The reference for the specified input stream.
             * */
            const String reference;

            /**
             * \brief Create a reader, that read from the specified input stream.
             * \param reference The reference for the specified input stream.
             * \param in The reference to the specified input stream.
             * */
            Reader(const String& reference, std::FILE* in);

            /**
             * \brief Clear the used memory resources (if any).
             * */
            ~Reader();

            /**
             * \brief Reads one character from the input stream.
             * \return The read character, or END_OF_FILE if EOF was reached.
             * */
            std::uint32_t read_one();

            /**
             * \brief Return the last one read character.
             * \return The last one read character.
             * */
            std::uint32_t last_one() const noexcept;

            /**
             * \brief Reuses the last character so that will be returned instead of the next read character.
             * */
            void reuse_last();

            /**
             * \brief Return the current line.
             * \return The current line.
             * */
            std::size_t get_line() const noexcept;

            /**
             * \brief Return the current column.
             * \return The current column.
             * */
            std::size_t get_column() const noexcept;

            /**
             * \brief Return the current location as a std::pair.
             * \return The current location. The first attribute is the line, the second the column.
             * */
            std::pair<std::size_t, std::size_t> get_location() const noexcept;

        private:
            /**
             * \brief The reference to the input stream.
             * */
            std::FILE* in;

            /**
             * \brief The current line in file.
             * */
            std::size_t line;

            /**
             * \brief The current column in file.
             * */
            std::size_t column;

            /**
             * \brief Tells if the input stream reached the EOF.
             * */
            bool eof_reached;

            /**
             * \brief Contains the last read character (if any).
             * */
            std::uint32_t last_char;

            /**
             * \brief Tells if the last read character should be reused.
             */
            bool reuse_last_required;

            /**
             * \brief The buffer capacity.
             * */
            std::size_t buffer_capacity;

            /**
             * \brief The buffer where the cached read bytes are stored.
             */
            std::uint8_t buffer[PREVC_UTIL_READER_DEFAULT_BUFFER_SIZE];

            /**
             * \brief The end of the data in the buffer.
             * */
            std::uint8_t* end;

            /**
             * \brief An iterator in the buffer.
             * */
            std::uint8_t* iterator;

            /**
             * \brief Fill the buffer.
             *
             * Puts any remaining byte at the start of the buffer (where the "iterator" attribute will point). Fill the
             * free buffer space with read bytes, adjusting the "end" attribute to point at the end of the read data. If
             * EOF is reached sets the "eof_reached" attribute.
             * */
            void fill_buffer();
        };
    }
}

#endif
