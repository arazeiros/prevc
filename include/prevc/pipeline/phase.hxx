
#ifndef PREVC_PIPELINE_PHASE_HXX
#define PREVC_PIPELINE_PHASE_HXX

namespace prevc
{
    namespace pipeline
    {
        class Phase;
    }
}

#include <prevc/pipeline/pipeline.hxx>

namespace prevc
{
    namespace pipeline
    {
        /**
         * \brief A single pipeline's phase.
         * */
        class Phase
        {
        public:
            /**
             * \brief Create a pipeline's phase.
             * \param pipeline The pipeline that owns this phase.
             * \sa complete()
             * */
            Phase(Pipeline* pipeline);

            /**
             * \brief Void implementation.
             * */
            virtual ~Phase();

            /**
             * \brief Complete the pipeline's phase, if not completed yet.
             * */
            void complete();

        protected:
            /**
             * \brief Implementation of this method should complete the pipeline's phase.
             * */
            virtual void complete_0() = 0;

            /**
             * \brief The pipeline that owns this phase
             * */
            Pipeline* pipeline;

        private:
            /**
             * \brief Tells if the pipeline was already completed.
             * */
            bool completed;
        };
    }
}

#endif
