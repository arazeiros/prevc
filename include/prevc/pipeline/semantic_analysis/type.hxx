
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPE_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_TYPE_HXX

#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            class TypeSystem;

            /**
             * \brief Represent a type in a Prev module.
             * */
            class Type: public util::String
            {
                friend TypeSystem;

            public:
                /**
                 * \brief Tells if a value can be assigned to a variable of this type.
                 * */
                const bool can_be_assigned;

                /**
                 * \brief Tells if a variable of this type can be passed as argument.
                 * */
                const bool can_be_passed;

                /**
                 * \brief Tells if a variable of this type can be returned from a function.
                 * */
                const bool can_be_returned;


                /**
                 * \brief Default implementation;
                 * */
                ~Type() = default;

            private:
                /**
                 * \brief Create a new type.
                 * \param id The id of the type.
                 * */
                Type(util::String&& id);
            };
        }
    }
}

#endif
