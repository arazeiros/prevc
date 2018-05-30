
#ifndef PREVC_PIPELINE_OUTPUTGENERATION_OUTPUTGENERATION_HXX
#define PREVC_PIPELINE_OUTPUTGENERATION_OUTPUTGENERATION_HXX

#include <prevc/pipeline/phase.hxx>
#include <prevc/pipeline/pipeline.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace output_generation
        {
            /**
             * \brief The output generation phase.
             * */
            class OutputGeneration: public Phase
            {
            public:
                /**
                 * \brief Create the output generation phase for the specified pipeline.
                 * \param pipeline The specified pipeline.
                 * */
                OutputGeneration(Pipeline* pipeline);

                /**
                 * \brief Releases the used resources.
                 * */
                virtual ~OutputGeneration();

            protected:
                /**
                 * \brief Implementation of this method should complete the phase.
                 * */
                void complete_0() override;
            };
        }
    }
}

#endif
