#include <prevc/util/reader.hxx>
#include <utf8.h>
#include <prevc/error.hxx>

namespace prevc
{
    namespace util
    {
        Reader::Reader(const util::String& reference, FILE* in):
            reference(reference),
            in(in),
            line(1),
            column(0),
            eof_reached(false),
            last_char(0),
            reuse_last_required(false),
            buffer_capacity(PREVC_UTIL_READER_DEFAULT_BUFFER_SIZE),
            end(&buffer[buffer_capacity]),
            iterator(end)
        {

        }

        Reader::~Reader()
        {
            
        }

        std::uint32_t Reader::read_one()
        {
            if (reuse_last_required)
            {
                reuse_last_required = false;
                ++column;
            }
            else
            {
                bool can_fail = true;

                while (true)
                {
                    std::size_t bytes_in_buffer = end - iterator;

                    if (bytes_in_buffer < 4)
                    {
                        if (bytes_in_buffer == 0)
                        {
                            if (eof_reached)
                            {
                                if (last_char == '\n')
                                {
                                    ++line;
                                    column = 1;
                                }
                                else
                                    ++column;

                                last_char = Reader::END_OF_FILE;
                                return last_char;
                            }

                            if (can_fail)
                            {
                                can_fail = false;
                                fill_buffer();
                                continue;
                            }
                            else
                            {
                                IOError::raise("EOF not reached, but can't read more characters (strange error)");
                            }
                        }
                        else
                        {
                            if (!utf8::is_valid(iterator, end))
                            {
                                if (eof_reached)
                                {
                                    CompileTimeError::raise(reference, {line, column + 1},
                                            "invalid UTF-8 character at end of file");
                                }

                                if (can_fail)
                                {
                                    can_fail = false;
                                    fill_buffer();
                                    continue;
                                }
                                else
                                {
                                    CompileTimeError::raise(reference, {line, column + 1},
                                            "invalid UTF-8 character");
                                }
                            }
                        }
                    }

                    break;
                }

                if (last_char == '\n')
                {
                    ++line;
                    column = 1;
                }
                else
                    ++column;

                try
                {
                    std::uint32_t read_char = utf8::next(iterator, end);
                    last_char = read_char;
                }
                catch (utf8::invalid_utf8 exception)
                {
                    CompileTimeError::raise(reference, get_location(),
                            "invalid UTF-8 character");
                }
            }

            return last_char;
        }

        std::uint32_t Reader::last_one() const noexcept
        {
            return (std::uint32_t) last_char;
        }

        void Reader::reuse_last()
        {
            if (reuse_last_required)
                InternalError::raise("could not reuse a character twice (if firstly is not read again)");

            reuse_last_required = true;
            --column;
        }

        std::size_t Reader::get_line() const noexcept
        {
            return line;
        }

        std::size_t Reader::get_column() const noexcept
        {
            return column;
        }

        std::pair<std::size_t, std::size_t> Reader::get_location() const noexcept
        {
            return {line, column};
        }

        void Reader::fill_buffer()
        {
            std::size_t bytes_in_buffer = end - iterator;

            for (std::uint8_t i = 0; i < bytes_in_buffer; ++i)
                buffer[i] = iterator[i];

            iterator = buffer;
            std::uint8_t* first_new = &buffer[bytes_in_buffer];
            std::size_t bytes_to_read = end - first_new;
            std::size_t read_bytes = std::fread(first_new, sizeof(std::uint8_t), bytes_to_read, in);

            if (read_bytes < bytes_to_read)
            {
                bool error_occurred = std::ferror(in) != 0;
                end = &first_new[read_bytes];

                if (error_occurred)
                    IOError::raise("error occurred while reading characters from the input stream");

                eof_reached = true;
            }
        }
    }
}
