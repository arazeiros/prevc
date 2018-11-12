
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAME_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAME_HXX

#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <cstdint>
#include <vector>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief Represent a function frame.
             * */
            class Frame
            {
            public:
                /**
                 * \brief The level of the frame.
                 * */
                const std::int32_t level;

                /**
                 * \brief Creates a new function frame.
                 * \brief The level of the frame.
                 * */
                Frame(std::int32_t level);

                /**
                 * \brief Default implementation.
                 * */
                virtual ~Frame() = default;

                /**
                 * \brief Allocate a new variable in the frame.
                 * \param variable The type of the variable to allocate.
                 * \return The index of the allocated variable.
                 * */
                std::uint64_t allocate_variable(const Type* variable);

            private:
                /**
                 * \brief All the variables in the frame.
                 * */
                std::vector<const Type*> variables;
            };
        }
    }
}

#endif
