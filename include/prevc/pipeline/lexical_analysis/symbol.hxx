
#ifndef PREVC_PIPELINE_LEXICALANALYSIS_SYMBOL_HXX
#define PREVC_PIPELINE_LEXICALANALYSIS_SYMBOL_HXX

#include <prevc/pipeline/lexical_analysis/token.hxx>
#include <prevc/util/location.hxx>
#include <prevc/util/string.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace lexical_analysis
        {
            /**
             * \brief A symbol in lexical analysis pipeline.
             * */
            class Symbol
            {
            public:
                /**
                 * \brief The token of the symbol.
                 * */
                const Token token;

                /**
                 * \brief The lexeme of the symbol.
                 * */
                const util::String lexeme;

                /**
                 * \brief The lexeme of the symbol.
                 * */
                const util::Location location;

                /**
                 * \brief The copy constructor.
                 * \param other The other object.
                 * */
                Symbol(const Symbol& other);

                /**
                 * \brief Create a symbol.
                 * \param token The token of the symbol.
                 * \param lexeme The token of the lexeme.
                 * \param location The token of the location.
                 * */
                Symbol(Token token, util::String&& lexeme, util::Location&& location);

                /**
                 * \brief Returns a string representation of this symbol.
                 * \return The representation in JSON format.
                 * */
                util::String to_string() const noexcept;
            };
        }
    }
}

#endif
