#include <prevc/pipeline/pipeline.hxx>
#include <prevc/pipeline/IR_generation/IR-generation.hxx>
#include <prevc/pipeline/lexical_analysis/lexical-analysis.hxx>
#include <prevc/pipeline/syntax_analysis/syntax-analysis.hxx>
#include <prevc/pipeline/derivation_analysis/derivation-analysis.hxx>

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

        Pipeline::Pipeline(const std::string& file_name):
            file_name(file_name),
            derivation_tree(nullptr),
            abstract_syntax_tree(nullptr),
            IR_module(nullptr)
        {

        }

        Pipeline::~Pipeline()
        {
            release_symbols_vector();
            release_derivation_tree();
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
            IR_generation::IRGeneration IR_generation(this);
            IR_generation.complete();
        }

        void Pipeline::release_symbols_vector()
        {
            symbols_vector.clear();
        }

        void Pipeline::release_derivation_tree()
        {
            zero_delete(&derivation_tree);
        }

        void Pipeline::release_abstract_syntax_tree()
        {
            zero_delete(&abstract_syntax_tree);
        }

        void Pipeline::release_IR_module()
        {
            auto context = &IR_module->getContext();
            zero_delete(&IR_module);
            delete context;
        }
    }
}