
#ifndef PREVC_UTIL_LOCATION_HXX
#define PREVC_UTIL_LOCATION_HXX

#include <cstdint>
#include <utility>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace util
    {
        /**
         * \brief Location in source code.
         *
         * Objects of this class are immutable.
         * */
        class Location
        {
        public:
            /**
             * \brief The beginning line of the location in source code.
             * */
            const std::size_t line_0;

            /**
             * \brief The beginning column of the location in source code.
             * */
            const std::size_t column_0;

            /**
             * \brief The ending line of the location in source code.
             * */
            const std::size_t line_1;

            /**
             * \brief The ending column of the location in source code.
             * */
            const std::size_t column_1;

            /**
             * \brief The move constructor.
             * \param other The other object.
             * */
            Location(Location&& other) noexcept;

            /**
             * \brief The copy constructor.
             * \param other The other object.
             * */
            Location(const Location& other) noexcept;

            /**
             * \brief Create a location, given the beginning/ending line and column.
             * \param line_0 The beginning line of the location in source code.
             * \param column_0 The beginning column of the location in source code.
             * \param line_1 The ending line of the location in source code.
             * \param column_1 The ending column of the location in source code.
             * */
            Location(std::size_t line_0, std::size_t column_0, std::size_t line_1, std::size_t column_1) noexcept;

            /**
             * \brief Create a location, given the beginning line and column and adding a length (on the same line).
             * \param line_0 The beginning line of the location in source code.
             * \param column_0 The beginning column of the location in source code.
             * \param length The length of the location. Default is 1.
             * */
            Location(std::size_t line_0, std::size_t column_0, std::size_t length = 1) noexcept;

            /**
             * \brief Create a location from the <line_0, column_0> pair.
             * \param location The <line_0, column_0> pair.
             *
             * Attributes line_1 and column_1 do respectively equals line_0 and column_0.
             * */
            Location(const std::pair<std::size_t, std::size_t>& location) noexcept;

            /**
             * \brief Create a location out of the two specified one. The location beginning will start at the
             *     beginning of the first location, the location ending will start at the ending of the second location.
             * \param first The first (beginning) location.
             * \param second The second (ending) location.
             * */
            Location(const Location& first, const Location& second) noexcept;

            /**
             * \brief Create a new location with some additive length (on the same line).
             * \param additive_length The additional length.
             * \return The new location.
             * */
            Location add_length(std::size_t additive_length) const noexcept;

            /**
             * \brief Returns a string representation of this location.
             * \return The representation in JSON format.
             * */
            util::String to_string() const noexcept;
        };
    }
}

#endif
