#include <prevc/pipeline/syntax_analysis/syntax-analysis.hxx>
#include <prevc/pipeline/syntax_analysis/derivation-tree-generator.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace syntax_analysis
        {
            SyntaxAnalysis::SyntaxAnalysis(Pipeline* pipeline):
                Phase(pipeline)
            {

            }

            SyntaxAnalysis::~SyntaxAnalysis() = default;

            void SyntaxAnalysis::complete_0()
            {
                auto builder = new SyntaxTreeBuilder(pipeline);
                pipeline->derivation_tree = builder->build();
                delete builder;
            }
        }
    }
}
