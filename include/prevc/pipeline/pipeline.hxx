
#ifndef PREVC_PIPELINE_PIPELINE_HXX
#define PREVC_PIPELINE_PIPELINE_HXX

namespace prevc
{
    namespace pipeline
    {
        class Pipeline;

        namespace AST
        {
            class ArrayType;
            class Atom;
            class BinaryOperation;
            class Compound;
            class Declarations;
            class FunctionCall;
            class FunctionDeclaration;
            class NamedType;
            class New;
            class Parenthesis;
            class PointerType;
            class PrimitiveType;
            class RecordType;
            class UnaryOperation;
            class TypeDeclaration;
            class VariableName;
        }

        namespace derivation_analysis
        {
            class DerivationAnalysis;
        }

        namespace lexical_analysis
        {
            class LexicalAnalysis;
        }

        namespace output_generation
        {
            class OutputGeneration;
        }

        namespace semantic_analysis
        {
            class Namespace;
            class SemanticAnalysis;
        }

        namespace syntax_analysis
        {
            class SyntaxAnalysis;
            class SyntaxTreeBuilder;
        }
    }
}

#include <string>
#include <llvm/IR/Module.h>
#include <prevc/pipeline/lexical_analysis/symbols-vector.hxx>
#include <prevc/pipeline/semantic_analysis/namespace.hxx>
#include <prevc/pipeline/semantic_analysis/type-system.hxx>
#include <prevc/pipeline/syntax_analysis/syntax-node.hxx>
#include <prevc/pipeline/AST/node.hxx>

namespace prevc
{
    namespace pipeline
    {
        /**
         * \brief The pipeline for a compilation of one module.
         * */
        class Pipeline
        {
            friend AST::ArrayType;
            friend AST::Atom;
            friend AST::BinaryOperation;
            friend AST::Compound;
            friend AST::Declarations;
            friend AST::FunctionCall;
            friend AST::FunctionDeclaration;
            friend AST::NamedType;
            friend AST::New;
            friend AST::Parenthesis;
            friend AST::PointerType;
            friend AST::PrimitiveType;
            friend AST::RecordType;
            friend AST::UnaryOperation;
            friend AST::VariableName;
            friend derivation_analysis::DerivationAnalysis;
            friend lexical_analysis::LexicalAnalysis;
            friend semantic_analysis::Namespace;
            friend semantic_analysis::SemanticAnalysis;
            friend syntax_analysis::SyntaxAnalysis;
            friend syntax_analysis::SyntaxTreeBuilder;
            friend output_generation::OutputGeneration;

        public:
            /**
             * \brief The filename of the module.
             * */
            const std::string file_name;

            /**
             * \brief Create a pipeline for the specified module.
             * \param file_name The filename of the module.
             * */
            Pipeline(const std::string& file_name);

            /**
             * \brief Release the used resources.
             * */
            virtual ~Pipeline();

            /**
             * \brief Compiles the module.
             * */
            void compile();

        private:
            /**
             * \brief The symbols vector.
             * Filled during the "lexical analysis" phase.
             * */
            lexical_analysis::SymbolsVector symbols_vector;

            /**
             * \brief The derivation tree of the module.
             * Calculated during the "syntax analysis" phase.
             * */
            syntax_analysis::SyntaxNode* derivation_tree;

            /**
             * \brief The global namespace of the module.
             * Calculated during the "semantic analysis" phase.
             * */
            semantic_analysis::Namespace* global_namespace;

            /**
             * \brief The type system, of the module.
             * Calculated during the "semantic analysis" phase.
             * */
            semantic_analysis::TypeSystem* type_system;

            /**
             * \brief Contains the current declaration that is under semantic check.
             * Or NULL if there is no such declaration.
             * */
            AST::TypeDeclaration* current_checking_declaration;

            /**
             * \brief The abstract syntax tree of the module.
             * Calculated during the "derivation analysis" phase.
             * */
            AST::Node* abstract_syntax_tree;

            /**
             * \brief The IR module of this module.
             * Calculated during the "IR generation" phase.
             * */
            llvm::Module* IR_module;

            /**
             * \brief Releases the symbols vector.
             * */
            void release_symbols_vector();

            /**
             * \brief Releases the derivation tree.
             * */
            void release_derivation_tree();

            /**
             * \brief Releases the global namespace.
             * */
            void release_global_namespace();

            /**
             * \brief Releases the type system.
             * */
            void release_type_system();

            /**
             * \brief Releases the abstract syntax tree.
             * */
            void release_abstract_syntax_tree();

            /**
             * \brief Releases the IR module.
             * */
            void release_IR_module();
        };
    }
}

#endif
