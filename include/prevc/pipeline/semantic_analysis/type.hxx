
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
                 * \brief The type kind.
                 * */
                const Kind kind;

                /**
                 * \brief The size of the type (in bytes).
                 * */
                const size_t size;

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

            protected:
                /**
                 * \brief Create a new type.
                 * \param id The id of the type.
                 * \param kind The kind of the type.
                 * \param size The size of the type (in bytes).
                 * */
                Type(Kind kind, size_t size);
            };
        }
    }
}

#endif
