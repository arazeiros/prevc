
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_POINTERTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_POINTERTYPE_HXX

#include <prevc/pipeline/semantic_analysis/concrete-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a pointar-type in a Prev module.
             * */
            class PointerType: public ConcreteType
            {
            public:
                /**
                 * \brief Type at which the pointer type is pointing at.
                 * */
                const Type* const sub;

                /**
                 * \brief Create a new pointer-type.
                 * \param sub Type at which the pointer type is pointing at.
                 * */
                PointerType(const Type* sub);

                /**
                 * \brief Default implementation;
                 * */
                virtual ~PointerType() = default;

                /**
                 * \brief Tells if this type and the one specified as the parameter equals.
                 * \param other The other type.
                 * \return True if they equals, false otherwise.
                 * */
                virtual bool equals(const Type* other) const noexcept override;

                /**
                 * \brief Tells if the type is cyclic.
                 * \param set The set containing the link types seen before.
                 * \return True if it is, false otherwise.
                 * */
                virtual bool is_cyclic(std::set<const LinkType*>* set) const noexcept override;

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
