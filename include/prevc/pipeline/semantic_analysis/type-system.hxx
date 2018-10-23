
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPESYSTEM_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPESYSTEM_HXX

#include <map>
#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief System that handle types of a Prev module.
             * */
            class TypeSystem
            {
            public:
                /**
                 * \brief Create a type system.
                 * */
                TypeSystem();

                /**
                 * \brief Release used resources.
                 * */
                virtual ~TypeSystem();

                /**
                 * \brief Provides reference to the type described by the specified type representation.
                 * \param type The specified type representation.
                 * \return The reference to the type.
                 * */
                const Type* get(util::String&& type);

                /**
                 * \brief Provides reference to the type described by the specified type representation.
                 * \param type The specified type representation.
                 * \return The reference to the type.
                 * */
                const Type* get(const util::String& type);

            private:
                /**
                 * \brief The structure for ordering string pointers.
                 * */
                struct Less
                {
                    bool operator()(const util::String* left, const util::String* right) const noexcept
                    {
                        return *left < *right;
                    }
                };

                /**
                 * \brief Map that caches all seen types.
                 * */
                std::map<util::String*, Type*, Less> types;
            };
        }
    }
}

#endif
