
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_RECORDTYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_RECORDTYPE_HXX

#include <prevc/pipeline/semantic_analysis/type.hxx>
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
                friend TypeSystem;

            public:
                /**
                 * \brief Default implementation;
                 * */
                virtual ~RecordType() = default;

                /**
                 * \brief Returns a string representation of this type.
                 * \return The representation.
                 * */
                virtual util::String to_string() const noexcept override;

            private:
                /**
                 * \brief Types of the components contained in the record.
                 * */
                const std::vector<const Type*> subs;

                /**
                 * \brief Create a new record-type.
                 * \param subs Types of the components contained in the record.
                 * */
                RecordType(std::vector<const Type*>&& subs);
            };
        }
    }
}

#endif
