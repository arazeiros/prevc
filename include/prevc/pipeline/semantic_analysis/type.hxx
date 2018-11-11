
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPE_HXX

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            class ArrayType;
            class AtomType;
            class PointerType;
            class RecordType;
            class Type;
        }
    }
}

#include <cstdint>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a type in a Prev module.
             * */
            class Type
            {
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
                 * \brief Default implementation;
                 * */
                virtual ~Type() = default;

                /**
                 * \brief Tells if this type is a link type.
                 * */
                virtual bool is_link() const noexcept;

                /**
                 * \brief Returns the id of the type.
                 * \return The id of the type.
                 * */
                virtual const util::String& get_id() const noexcept = 0;

                /**
                 * \brief Returns the id of the type.
                 * \return The id of the type.
                 * */
                virtual Kind get_kind() const noexcept = 0;

                /**
                 * \brief Tells if the type is an array-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_array() const noexcept;

                /**
                 * \brief Tells if the type is an atom-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_atom() const noexcept;

                /**
                 * \brief Tells if the type is a record-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_record() const noexcept;

                /**
                 * \brief Tells if the type is a pointer-type.
                 * \return True if it is, false otherwise.
                 * */
                bool is_pointer() const noexcept;

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
                 * \brief Tells if a value can be assigned to a variable of this type.
                 * \return True if can be assigned, false otherwise.
                 * */
                bool can_be_assigned() const;

                /**
                 * \brief Tells if a variable of this type can be passed as argument.
                 * \return True if can be passed, false otherwise.
                 * */
                bool can_be_passed() const;

                /**
                 * \brief Tells if a variable of this type can be returned from a function.
                 * \return True if can be returned, false otherwise.
                 * */
                bool can_be_returned() const;

                /**
                 * \brief Converts this to an atom-type.
                 * \return The converted this.
                 * */
                virtual const AtomType* as_atom() const;

                /**
                 * \brief Converts this to an array-type.
                 * \return The converted this.
                 * */
                virtual const ArrayType* as_array() const;

                /**
                 * \brief Converts this to an record-type.
                 * \return The converted this.
                 * */
                virtual const RecordType* as_record() const;

                /**
                 * \brief Converts this to an pointer-type.
                 * \return The converted this.
                 * */
                virtual const PointerType* as_pointer() const;

                /**
                 * \brief Tells if this type and the one specified as the parameter equals.
                 * \param other The other type.
                 * \return True if they equals, false otherwise.
                 *
                 * Note that two records equals even if they have different components names, but the same types
                 * in the same order.
                 * */
                virtual bool equals(const Type* other) const noexcept = 0;

                /**
                 * \brief Returns a string representation of a type.
                 * \return The representation.
                 * */
                virtual util::String to_string() const noexcept = 0;
            };
        }
    }
}

#endif
