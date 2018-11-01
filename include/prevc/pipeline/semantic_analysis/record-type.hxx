
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_RECORDTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_RECORDTYPE_HXX

#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <optional>
#include <vector>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a record-type in a Prev module.
             * */
            class RecordType: public Type
            {
            public:
                /**
                 * \brief Types of the components contained in the record.
                 * */
                const std::vector<std::pair<util::String, const Type*>> subs;

                /**
                 * \brief Create a new record-type.
                 * \param subs Types of the components contained in the record.
                 * */
                RecordType(std::vector<std::pair<util::String, const Type*>>&& subs);

                /**
                 * \brief Default implementation;
                 * */
                virtual ~RecordType() = default;

                /**
                 * \brief Tells if this type and the one specified as the parameter equals.
                 * \param other The other type.
                 * \return True if they equals, false otherwise.
                 *
                 * Note that two records equals even if they have different components names, but the same types
                 * in the same order.
                 * */
                virtual bool equals(const Type& other) const noexcept override;

                /**
                 * \brief Returns the type of the specified component (if present).
                 * \param component_name The name of the component.
                 * \return The type of the component, or nothing if component is not present in this record.
                 * */
                std::optional<const Type*> get_type_of(const util::String& component_name) const noexcept;

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
