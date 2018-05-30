#include <prevc/pipeline/lexical_analysis/symbol.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace lexical_analysis
        {
            Symbol::Symbol(const Symbol& other):
                    token(other.token),
                    lexeme(other.lexeme),
                    location(other.location)
            {

            }

            Symbol::Symbol(Token token, util::String&& lexeme, util::Location&& location):
                token(token),
                lexeme(std::move(lexeme)),
                location(std::move(location))
            {

            }

            util::String Symbol::to_string() const noexcept
            {
                return util::String::format("{\"token\": \"%s\", \"lexeme\": \"%s\", \"location\": %s}",
                    lexical_analysis::to_string(token),
                    lexeme.c_str(),
                    location.to_string().c_str());
            }
        }
    }
}
