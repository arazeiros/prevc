#include <prevc/util/location.hxx>

namespace prevc
{
    namespace util
    {
        Location::Location(Location&& other) noexcept:
            Location(other)
        {

        }

        Location::Location(const Location& other) noexcept:
            Location(other.line_0, other.column_0, other.line_1, other.column_1)
        {

        }

        Location::Location(std::size_t line_0, std::size_t column_0, std::size_t line_1, std::size_t column_1) noexcept:
            line_0(line_0),
            column_0(column_0),
            line_1(line_1),
            column_1(column_1)
        {

        }

        Location::Location(std::size_t line_0, std::size_t column_0, std::size_t length) noexcept:
            Location(line_0, column_0, line_0, column_0 + length - 1)
        {

        }

        Location::Location(const std::pair<std::size_t, std::size_t>& location) noexcept:
            Location(location.first, location.second)
        {

        }

        Location::Location(const prevc::util::Location& first, const prevc::util::Location& second) noexcept:
            Location(first.line_0, first.column_0, second.line_1, second.column_1)
        {

        }

        Location Location::add_length(std::size_t additive_length) const noexcept
        {
            return {line_0, column_0, line_1, column_1 + additive_length};
        }

        util::String Location::to_string() const noexcept
        {
            return util::String::format(R"({"line_0": "%zu", "column_0": "%zu", "line_1": "%zu", "column_1": "%zu"})",
                line_0, column_0, line_1, column_1);
        }
    }
}
