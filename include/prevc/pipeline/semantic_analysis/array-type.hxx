
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_ARRAYTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_ARRAYTYPE_HXX

#include <prevc/pipeline/semantic_analysis/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a array-type in a Prev module.
             * */
            class ArrayType: public Type
            {
            public:
                /**
                 * \brief The length of the array.
                 * */
                const size_t length;

                /**
                 * \brief Type of the components contained in the array.
                 * */
                const Type* const sub;

                /**
                 * \brief Create a new array-type.
                 * \param sub Type of the components contained in the array.
                 * \param length The length of the array.
                 * */
                ArrayType(const Type* sub, size_t length);

                /**
                 * \brief Default implementation;
                 * */
                virtual ~ArrayType() = default;

                /**
                 * \brief Tells if this type and the one specified as the parameter equals.
                 * \param other The other type.
                 * \return True if they equals, false otherwise.
                 * */
                virtual bool equals(const Type& other) const noexcept override;

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
