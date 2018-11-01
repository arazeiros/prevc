#include <prevc/pipeline/semantic_analysis/semantic-analysis.hxx>
#include <prevc/pipeline/semantic_analysis/atom-type.hxx>
#include <prevc/pipeline/semantic_analysis/namespace.hxx>
#include <prevc/pipeline/semantic_analysis/type.hxx>
#include <prevc/pipeline/AST/expression.hxx>

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
                using SType = semantic_analysis::Type;
                using SAtom = semantic_analysis::AtomType;

                // safe cast: syntax analysis restrict root of a AST to be an expression
                auto root = (AST::Expression*) pipeline->abstract_syntax_tree;

                root->check_semantics();
                auto type = root->get_semantic_type();

                if (type->kind != SType::Kind::ATOM || ((SAtom*) type)->atomKind != SAtom::Kind::INT)
                    CompileTimeError::raise(pipeline->file_name, root->location, util::String::format(
                            "the root expression of the module must be of type `int`, but the "
                            "given one is of type `%s`", type->to_string().c_str()));
            }
        }
    }
}

