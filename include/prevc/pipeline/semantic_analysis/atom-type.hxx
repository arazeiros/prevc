
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_ATOMTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_ATOMTYPE_HXX

#include <prevc/pipeline/semantic_analysis/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent an atom-type in a Prev module.
             * */
            class AtomType: public Type
            {
                friend TypeSystem;

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
                 * \brief Tells if a value can be assigned to a variable of this type.
                 * \return True if is not of kind VOID.
                 * */
                virtual bool can_be_assigned() const override;

                /**
                 * \brief Tells if a variable of this type can be passed as argument.
                 * \return True if is not of kind VOID.
                 * */
                virtual bool can_be_passed() const override;

                /**
                 * \brief Tells if a variable of this type can be returned from a function.
                 * \return True, always.
                 * */
                virtual bool can_be_returned() const override;

                /**
                 * \brief Default implementation;
                 * */
                virtual ~AtomType() = default;

            private:
                /**
                 * \brief Create a new atom-type.
                 * \param kind The kind of the atom-type
                 * */
                AtomType(Kind kind);
            };
        }
    }
}

#endif
