#include <prevc/pipeline/semantic_analysis/frame-system.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            FrameSystem::FrameSystem() = default;

            void FrameSystem::push()
            {
                auto frame = new Frame((std::int32_t) this->frames.size());
                this->frames.push(frame);
            }

            const Frame* FrameSystem::pop()
            {
                auto frame = this->frames.top();
                this->frames.pop();
                return frame;
            }
        }
    }
}
