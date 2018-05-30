
#ifndef PREVC_PIPELINE_SYNTAXANALYSIS_SYNTAXANALYSIS_HXX
#define PREVC_PIPELINE_SYNTAXANALYSIS_SYNTAXANALYSIS_HXX

#include <prevc/pipeline/phase.hxx>
#include <prevc/pipeline/pipeline.hxx>
#include <prevc/pipeline/lexical_analysis/symbols-vector.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace syntax_analysis
        {
            /**
             * \brief The syntax analysis phase.
             * */
            class SyntaxAnalysis: public Phase
            {
            public:
                /**
                 * \brief Create the syntax analysis phase for the specified pipeline.
                 * \param pipeline The specified pipeline.
                 * */
                SyntaxAnalysis(Pipeline* pipeline);

                /**
                 * \brief Releases the used resources.
                 * */
                virtual ~SyntaxAnalysis();

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
