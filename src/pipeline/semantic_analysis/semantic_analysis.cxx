#include <prevc/pipeline/semantic_analysis/semantic-analysis.hxx>
#include <prevc/pipeline/semantic_analysis/namespace.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace semantic_analysis
        {
            SemanticAnalysis::SemanticAnalysis(Pipeline* pipeline):
                Phase(pipeline)
            {
                pipeline->global_namespace = new Namespace;
                pipeline->type_system = new TypeSystem;
            }

            SemanticAnalysis::~SemanticAnalysis()
            {
                pipeline->release_global_namespace();
            }

            void SemanticAnalysis::complete_0()
            {
                pipeline->abstract_syntax_tree->check_semantics();
            }
        }
    }
}

