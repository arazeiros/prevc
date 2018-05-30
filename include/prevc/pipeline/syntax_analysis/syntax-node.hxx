
#ifndef PREVC_PIPELINE_SYNTAXANALYSIS_SYNTAXNODE_HXX
#define PREVC_PIPELINE_SYNTAXANALYSIS_SYNTAXNODE_HXX

#include <prevc/pipeline/lexical_analysis/symbol.hxx>
#include <prevc/pipeline/syntax_analysis/variable-type.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace syntax_analysis
        {
            /**
             * \brief Class that represent a single syntax node (a terminal or a variable).
             * */
            class SyntaxNode
            {
            public:
                /**
                 * \brief Empty implementation destructor.
                 * */
                virtual ~SyntaxNode() {}

                /**
                 * \brief Tells if the node is a terminal node.
                 * \return True if it's terminal, false otherwise.
                 * */
                virtual bool is_terminal() const noexcept = 0;

                /**
                 * \brief Tells if the node is a variable node.
                 * \return True if it's variable, false otherwise.
                 * */
                virtual bool is_variable() const noexcept = 0;

                /**
                 * \brief Returns a string representation of this node.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept = 0;
            };

            /**
             * \brief Class that represent a terminal syntax node.
             * */
            class SyntaxTerminal: public SyntaxNode
            {
            public:
                /**
                 * \brief The symbol that represents the terminal node.
                 * */
                const lexical_analysis::Symbol& symbol;

                /**
                 * \brief Create a variable syntax node, that contains specified symbol.
                 * */
                SyntaxTerminal(const lexical_analysis::Symbol& symbol);

                /**
                 * \brief Empty implementation destructor.
                 * */
                virtual ~SyntaxTerminal() {}

                /**
                 * \brief Tells if the node is a terminal node.
                 * \return Always returns true.
                 * */
                virtual bool is_terminal() const noexcept override;

                /**
                 * \brief Tells if the node is a variable node.
                 * \return Always returns false.
                 * */
                virtual bool is_variable() const noexcept override;

                /**
                 * \brief Returns a string representation of this terminal.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };

            /**
             * \brief Class that represent a variable syntax node.
             * */
            class SyntaxVariable: public SyntaxNode
            {
            public:
                /**
                 * \brief The type of this variable.
                 * */
                const VariableType type;

                /**
                 * \brief The nodes produced by this variable.
                 * */
                const std::vector<const SyntaxNode*> nodes;

                /**
                 * \brief Create a variable syntax node, of a specific type, that contains specified nodes
                 *     produced by this variable.
                 * \param type The type of this variable
                 * \param nodes The nodes produced by this variable.
                 * */
                SyntaxVariable(VariableType type, std::vector<const SyntaxNode*>&& nodes);

                /**
                 * \brief Releases the nodes.
                 * */
                virtual ~SyntaxVariable();

                /**
                 * \brief Tells if the node is a terminal node.
                 * \return Always returns false.
                 * */
                virtual bool is_terminal() const noexcept override;

                /**
                 * \brief Tells if the node is a variable node.
                 * \return Always returns true.
                 * */
                virtual bool is_variable() const noexcept override;

                /**
                 * \brief Returns a string representation of this variable.
                 * \return The representation in JSON format.
                 * */
                virtual util::String to_string() const noexcept override;
            };
        }
    }
}

#endif
