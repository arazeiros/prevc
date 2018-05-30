
#ifndef PREVC_PIPELINE_LEXICALANALYSIS_LEXICALANALYSIS_HXX
#define PREVC_PIPELINE_LEXICALANALYSIS_LEXICALANALYSIS_HXX

#include <prevc/pipeline/phase.hxx>
#include <prevc/pipeline/pipeline.hxx>
#include <prevc/pipeline/lexical_analysis/symbols-vector.hxx>
#include <prevc/util/reader.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace lexical_analysis
        {
            /**
             * \brief The lexical analysis phase.
             * */
            class LexicalAnalysis: public Phase
            {
            public:
                /**
                 * \brief Create the lexical analysis phase for the specified pipeline.
                 * \param pipeline The pipeline.
                 * */
                LexicalAnalysis(Pipeline* pipeline);

                /**
                 * \brief Releases the used resources.
                 * */
                virtual ~LexicalAnalysis();

            protected:
                /**
                 * \brief Implementation of this method should transform input data stored in attribute "in" into output
                 *     data and store that in the attribute "out" for the next pipeline.
                 * */
                void complete_0() override;

            private:
                /**
                 * \brief The input stream from which the analyzer is reading from.
                 * */
                FILE* input_stream;

                /**
                 * \brief The reader, that this phase is using.
                 * */
                util::Reader reader;

                /**
                 * \brief Consume the rest of the inline comment from the reader.
                 * */
                void consume_inline_comment();

                /**
                 * \brief Consumes the rest of the integer literal from the reader and stores the symbol in the output
                 *     vector.
                 * */
                void consume_integer_literal();

                /**
                 * \brief Consumes the rest of the character literal from the reader and stores the symbol in the
                 *     output vector.
                 * */
                void consume_char_literal();

                /**
                 * \brief Consumes the rest of a symbol starting with a letter. The symbol can be a literal, keyword
                 *     or an identifier.
                 * */
                void consume_alpha_numeric();

                /**
                 * \brief Consume a symbol from the reader.
                 * \param scope_applied Tells if the scope indentation was already applied to the current line.
                 * \param spaces_count The number of consumed spaces at the beginning of the line.
                 * \return True if the end of line was reached, false otherwise.
                 * */
                bool consume_symbol();

                /**
                 * \brief Consume a line from the reader.
                 * */
                void consume_line();

                /**
                 * \brief Finalize the output vector.
                 *
                 * Add the ending "scope end" symbols and the EOF symbol.
                 * */
                void finalize_vector();
            };
        }
    }
}

#endif
