
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPE_HXX

#include <cstdint>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            class TypeSystem;

            /**
             * \brief Represent a type in a Prev module.
             * */
            class Type
            {
                friend TypeSystem;

            public:
                /**
                 * \brief Enumeration of possible type kinds.
                 * */
                enum class Kind
                {
                    ATOM,
                    POINTER,
                    ARRAY,
                    RECORD
                };

                /**
                 * \brief The id of the type (AKA semantic representation).
                 * */
                const util::String id;

                /**
                 * \brief The type kind.
                 * */
                const Kind kind;

                /**
                 * \brief Tells if the type is a atom-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_atom() const noexcept;

                /**
                 * \brief Tells if the type is a pointer-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_pointer() const noexcept;

                /**
                 * \brief Tells if the type is an array-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_array() const noexcept;

                /**
                 * \brief Tells if the type is a record-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_record() const noexcept;

                /**
                 * \brief Tells if the type is an char-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_char() const noexcept;

                /**
                 * \brief Tells if the type is an int-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_int() const noexcept;

                /**
                 * \brief Tells if the type is a void-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_void() const noexcept;

                /**
                 * \brief Tells if the type is a bool-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_bool() const noexcept;

                /**
                 * \brief Tells if this type and the one specified as the parameter equals.
                 * \param other The other type.
                 * \return True if they equals, false otherwise.
                 *
                 * Note that two records equals even if they have different components names, but the same types
                 * in the same order.
                 * */
                virtual bool equals(const Type& other) const noexcept = 0;

                /**
                 * \brief Tells if a value can be assigned to a variable of this type.
                 * \return True if can be assigned, false otherwise.
                 * */
                virtual bool can_be_assigned() const;

                /**
                 * \brief Tells if a variable of this type can be passed as argument.
                 * \return True if can be passed, false otherwise.
                 * */
                virtual bool can_be_passed() const;

                /**
                 * \brief Tells if a variable of this type can be returned from a function.
                 * \return True if can be returned, false otherwise.
                 * */
                virtual bool can_be_returned() const;

                /**
                 * \brief Default implementation;
                 * */
                virtual ~Type() = default;

                /**
                 * \brief Returns a string representation of a type.
                 * \return The representation.
                 * */
                virtual util::String to_string() const noexcept = 0;

            protected:
                /**
                 * \brief Create a new type.
                 * \param id The id of the type.
                 * \param kind The kind of the type.
                 * */
                Type(util::String&& id, Kind kind);
            };
        }
    }
}

#endif
