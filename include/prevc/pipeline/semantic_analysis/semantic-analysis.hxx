
#ifndef PREVC_PIPELINE_SEMANTICANALYSIS_SEMANTICANALYSIS_HXX
#define PREVC_PIPELINE_SEMANTICANALYSIS_SEMANTICANALYSIS_HXX

#include <prevc/pipeline/phase.hxx>
#include <prevc/pipeline/pipeline.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            /**
             * \brief The semantic analysis phase.
             * */
            class SemanticAnalysis: public Phase
            {
            public:
                /**
                 * \brief Create the semantic analysis phase for the specified pipeline.
                 * \param pipeline The pipeline.
                 * */
                SemanticAnalysis(Pipeline* pipeline);

                /**
                 * \brief Releases the used resources.
                 * */
                virtual ~SemanticAnalysis();

            protected:
                /**
                 * \brief Implementation of this method should transform input data into output
                 *     data for the next pipeline.
                 * */
                void complete_0() override;
            };
        }
    }
}

#endif
