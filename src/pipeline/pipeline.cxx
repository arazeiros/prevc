#include <prevc/pipeline/pipeline.hxx>
#include <prevc/pipeline/lexical_analysis/lexical-analysis.hxx>
#include <prevc/pipeline/output_generation/output-generation.hxx>
#include <prevc/pipeline/semantic_analysis/semantic-analysis.hxx>
#include <prevc/pipeline/syntax_analysis/syntax-analysis.hxx>
#include <prevc/pipeline/derivation_analysis/derivation-analysis.hxx>
#include <prevc/pipeline/AST/expression.hxx>

namespace prevc
{
    namespace pipeline
    {
        template <typename E>
        static inline void zero_delete(E** element)
        {
            if (*element == nullptr)
                return;

            delete *element;
            *element = nullptr;
        }

        Pipeline::Pipeline(const Settings* settings, const std::string& file_name):
            settings(settings),
            file_name(file_name),
            derivation_tree(nullptr),
            next_declaration_id(1),
            global_namespace(nullptr),
            type_system(nullptr),
            frame_system(nullptr),
            current_checking_declaration(nullptr),
            abstract_syntax_tree(nullptr),
            IR_module(nullptr)
        {

        }

        Pipeline::~Pipeline()
        {
            release_symbols_vector();
            release_derivation_tree();
            release_global_namespace();
            release_type_system();
            release_frame_system();
            release_abstract_syntax_tree();
            release_IR_module();
        }

        void Pipeline::compile()
        {
            lexical_analysis::LexicalAnalysis lexical_analysis(this);
            lexical_analysis.complete();
            syntax_analysis::SyntaxAnalysis syntax_analysis(this);
            syntax_analysis.complete();
            derivation_analysis::DerivationAnalysis derivation_analysis(this);
            derivation_analysis.complete();
            semantic_analysis::SemanticAnalysis semantic_analysis(this);
            semantic_analysis.complete();
            output_generation::OutputGeneration output_generation(this);
            output_generation.complete();
        }

        void Pipeline::release_symbols_vector()
        {
            symbols_vector.clear();
        }

        void Pipeline::release_derivation_tree()
        {
            zero_delete(&derivation_tree);
        }

        void Pipeline::release_global_namespace()
        {
            zero_delete(&global_namespace);
        }

        void Pipeline::release_type_system()
        {
            zero_delete(&type_system);
        }

        void Pipeline::release_frame_system()
        {
            zero_delete(&frame_system);
        }

        void Pipeline::release_abstract_syntax_tree()
        {
            zero_delete(&abstract_syntax_tree);
        }

        void Pipeline::release_IR_module()
        {
            if (IR_module == nullptr)
                return;

            auto context = &IR_module->getContext();
            delete IR_module;
            delete context;
            IR_module = nullptr;
        }
    }
}
