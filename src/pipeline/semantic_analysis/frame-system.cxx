#include <prevc/pipeline/semantic_analysis/frame-system.hxx>
#include <prevc/pipeline/semantic_analysis/pointer-type.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            FrameSystem::FrameSystem() = default;

            FrameSystem::~FrameSystem() = default;

            std::uint64_t FrameSystem::get_level() const
            {
                return (std::uint64_t) this->frames.size() - 1;
            }

            Frame* FrameSystem::get_current() const
            {
                return this->frames.top();
            }

            void FrameSystem::push()
            {
                auto level = (std::int32_t) this->frames.size();
                auto static_link = (level <= 1) ? nullptr : this->frames.top();
                auto frame = new Frame(level, static_link);
                this->frames.push(frame);
            }

            const Frame* FrameSystem::pop()
            {
                auto frame = this->frames.top();
                this->frames.pop();
                return frame;
            }

            std::pair<Frame*, std::uint64_t> FrameSystem::allocate_variable(const Type* variable)
            {
                auto frame = this->frames.top();
                return std::make_pair(frame, frame->allocate_variable(variable));
            }
        }
    }
}
