
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
