
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAME_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAME_HXX

#include <cstdint>

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
            };
        }
    }
}

#endif
