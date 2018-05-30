
#ifndef PREVC_PIPELINE_DERIVATIONANALYSIS_DERIVATIONANALYSIS_HXX
#define PREVC_PIPELINE_DERIVATIONANALYSIS_DERIVATIONANALYSIS_HXX

#include <prevc/pipeline/phase.hxx>
#include <prevc/pipeline/pipeline.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace derivation_analysis
        {
            /**
             * \brief The phase in which the derivation tree from "syntax analysis" is analysed and the abstract
             *     syntax tree is created.
             * */
            class DerivationAnalysis: public Phase
            {
            public:
                /**
                 * \brief Create the "derivation analysis" phase for the specified pipeline.
                 * \param pipeline The specified pipeline.
                 * */
                DerivationAnalysis(Pipeline* pipeline);

                /**
                 * \brief Releases the used resources.
                 * */
                virtual ~DerivationAnalysis();

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
