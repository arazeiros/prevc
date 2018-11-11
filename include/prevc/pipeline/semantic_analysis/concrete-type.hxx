
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_CONCRETETYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_CONCRETETYPE_HXX

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            class ConcreteType;
        }
    }
}

#include <prevc/pipeline/semantic_analysis/type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a concrete type in a Prev module.
             * */
            class ConcreteType: public Type
            {
            public:
                /**
                 * \brief Default implementation;
                 * */
                virtual ~ConcreteType() = default;

                /**
                 * \brief Returns the id of the type.
                 * \return The id of the type.
                 * */
                virtual const util::String& get_id() const noexcept override;

                /**
                 * \brief Returns the id of the type.
                 * \return The id of the type.
                 * */
                virtual Kind get_kind() const noexcept override;

            protected:
                /**
                 * \brief Create a new type.
                 * \param id The id of the type.
                 * \param kind The kind of the type.
                 * */
                ConcreteType(util::String&& id, Kind kind);

            private:
                /**
                 * \brief The id of the concrete type (AKA semantic representation).
                 * */
                const util::String id;

                /**
                 * \brief The type kind.
                 * */
                const Kind kind;
            };
        }
    }
}

#endif
