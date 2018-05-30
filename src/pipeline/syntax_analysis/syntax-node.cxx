#include <prevc/pipeline/syntax_analysis/syntax-node.hxx>
#include <utility>
#include <iostream>
#include <sstream>

namespace prevc
{
    namespace pipeline
    {
        namespace syntax_analysis
        {
            SyntaxTerminal::SyntaxTerminal(const lexical_analysis::Symbol& symbol):
                symbol(symbol)
            {

            }

            bool SyntaxTerminal::is_terminal() const noexcept
            {
                return true;
            }

            bool SyntaxTerminal::is_variable() const noexcept
            {
                return false;
            }

            util::String SyntaxTerminal::to_string() const noexcept
            {
                return util::String::format(R"({"type": "terminal", "symbol": %s})",
                    symbol.to_string().c_str());
            }

            SyntaxVariable::SyntaxVariable(VariableType type, std::vector<const SyntaxNode*>&& nodes):
                type(type),
                nodes(std::move(nodes))
            {

            }

            SyntaxVariable::~SyntaxVariable()
            {
                for (auto node : nodes)
                    delete node;
            }

            bool SyntaxVariable::is_terminal() const noexcept
            {
                return false;
            }

            bool SyntaxVariable::is_variable() const noexcept
            {
                return true;
            }

            util::String SyntaxVariable::to_string() const noexcept
            {
                std::stringbuf buffer;
                std::ostream out(&buffer);
                auto i = nodes.begin();
                auto n = nodes.end();
                out << R"({"type": "variable", )";
                out << R"("variable": ")" << syntax_analysis::to_string(this->type) << R"(", "nodes": [)";

                if (!nodes.empty())
                {
                    out << (**i).to_string().c_str();

                    while (++i != n)
                    {
                        out << ", ";
                        out << (**i).to_string().c_str();
                    }
                }
                out << "]}";
                return buffer.str();
            }
        }
    }
}
