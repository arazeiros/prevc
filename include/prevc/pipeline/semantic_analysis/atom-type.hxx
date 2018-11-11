
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_ATOMTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_ATOMTYPE_HXX

#include <prevc/pipeline/semantic_analysis/concrete-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent an atom-type in a Prev module.
             * */
            class AtomType: public ConcreteType
            {
            public:
                /**
                 * \brief Enumeration of possible atom-type kinds.
                 * */
                enum class Kind
                {
                    VOID,
                    BOOL,
                    CHAR,
                    INT
                };

                /**
                 * \brief The atom-type kind.
                 * */
                const Kind atomKind;

                /**
                 * \brief Create a new atom-type.
                 * \param kind The kind of the atom-type
                 * */
                AtomType(Kind kind);

                /**
                 * \brief Default implementation;
                 * */
                virtual ~AtomType() = default;

                /**
                 * \brief Tells if this type and the one specified as the parameter equals.
                 * \param other The other type.
                 * \return True if they equals, false otherwise.
                 * */
                virtual bool equals(const Type* other) const noexcept override;

                /**
                 * \brief Returns a string representation of this type.
                 * \return The representation.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#endif
