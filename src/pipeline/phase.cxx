#include <prevc/pipeline/phase.hxx>
#include <utility>

namespace prevc
{
    namespace pipeline
    {
        Phase::Phase(Pipeline* pipeline):
            pipeline(pipeline),
            completed(false)
        {

        }

        Phase::~Phase()
        {

        }

        void Phase::complete()
        {
            if (completed)
                return;

            complete_0();
            completed = true;
        }
    }
}
