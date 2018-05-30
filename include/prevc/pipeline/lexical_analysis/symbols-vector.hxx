
#ifndef PREVC_PIPELINE_LEXICALANALYSIS_SYMBOLSVECTOR_HXX
#define PREVC_PIPELINE_LEXICALANALYSIS_SYMBOLSVECTOR_HXX

#include <vector>
#include <prevc/pipeline/lexical_analysis/symbol.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace lexical_analysis
        {
            /**
             * \brief A vector of symbols in lexical analysis pipeline.
             * */
            class SymbolsVector: public std::vector<Symbol>
            {
            public:
                /**
                 * \brief Returns a string representation of this symbols vector.
                 * \return The representation in JSON format.
                 * */
                util::String to_string() const noexcept;
            };
        }
    }
}

#endif
