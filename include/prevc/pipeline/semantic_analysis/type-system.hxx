
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPESYSTEM_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPESYSTEM_HXX

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
                 * \brief Provides reference to the type described by the specified type representation.
                 * \param type The specified type representation.
                 * \return The reference to the type. Returns NULL if the type can not be generated.
                 * */
                const Type* get(util::String&& type);

                /**
                 * \brief Provides reference to the type described by the specified type representation.
                 * \param type The specified type representation.
                 * \return The reference to the type. Returns NULL if the type can not be generated.
                 * */
                const Type* get(const util::String& type);

            private:
                /**
                 * \brief Map that caches all seen types.
                 * */
                std::map<util::String, const Type*> types;

                /**
                 * \brief Generate the type out of the id.
                 * \return The generated type or NULL if id does not represent a valid type.
                 * */
                static const Type* generate(const util::String& id);
            };
        }
    }
}

#endif
