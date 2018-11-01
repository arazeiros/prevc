
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPESYSTEM_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPESYSTEM_HXX

#include <functional>
#include <map>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            class Type;

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
                 * \brief Provides reference to the type described by the specified semantic type representation.
                 * \param id The semantic type representation.
                 * \param provider Should provide the type in case that the type does not already exist (the type
                 *     created in this manner will be cached). Should return NULL if can not be generated.
                 * \return The reference to the type. Returns NULL if the type can not be generated.
                 * */
                const Type* get_or_insert(const util::String& id, std::function<const Type*()>&& provider);

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
                std::map<const util::String*, const Type*, Less> types;
            };
        }
    }
}

#endif
