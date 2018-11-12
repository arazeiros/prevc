
#ifndef PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAMESYSTEM_HXX
#define PREVC_PIPELINE_SEMANTIC_ANALYSIS_FRAMESYSTEM_HXX

#include <prevc/pipeline/semantic_analysis/frame.hxx>
#include <stack>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief System that handle function frames of a Prev module.
             * */
            class FrameSystem
            {
            public:
                /**
                 * \brief Create a frame system.
                 * */
                FrameSystem();

                /**
                 * \brief Default implementation.
                 * */
                virtual ~FrameSystem() = default;

                /**
                 * \brief Adds a new frame on the top.
                 * */
                 void push();

                /**
                 * \brief Pops the current frame.
                 * \return The current frame.
                 *
                 * The returned frame is not memory managed, so it should be deleted with a `delete`.
                 * */
                const Frame* pop();

            private:
                /**
                 * \brief The stack of currently used frames.
                 * */
                std::stack<Frame*> frames;
            };
        }
    }
}

#endif
