#include <prevc/pipeline/semantic_analysis/frame.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            Frame::Frame(std::int32_t level):
                level(level)
            {

            }

            std::uint64_t Frame::allocate_variable(const Type* variable)
            {
                std::uint64_t index = this->variables.size();
                this->variables.push_back(variable);
                return index;
            }
        }
    }
}
