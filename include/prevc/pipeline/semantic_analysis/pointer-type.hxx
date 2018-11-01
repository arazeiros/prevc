
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_POINTERTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_POINTERTYPE_HXX

#include <prevc/pipeline/semantic_analysis/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a pointar-type in a Prev module.
             * */
            class PointerType: public Type
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
                 * \brief Tells if a value can be assigned to a variable of this type.
                 * \return True, always.
                 * */
                virtual bool can_be_assigned() const override;

                /**
                 * \brief Tells if a variable of this type can be passed as argument.
                 * \return True, always.
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
                virtual ~PointerType() = default;

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
