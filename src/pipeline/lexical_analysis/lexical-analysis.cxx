#include <prevc/pipeline/lexical_analysis/lexical-analysis.hxx>
#include <cstring>
#include <cctype>

namespace prevc
{
    namespace pipeline
    {
        namespace lexical_analysis
        {
            LexicalAnalysis::LexicalAnalysis(Pipeline* pipeline):
                Phase(pipeline),
                input_stream([&] () -> FILE*
                    {
                        const char* file_name = pipeline->file_name.c_str();
                        std::FILE* tmp = std::fopen(file_name, "rb");

                        if (tmp == nullptr)
                            IOError::raise(util::String::format(R"(could not open file: "%s")", file_name));

                        return tmp;
                    } ()),
                reader(pipeline->file_name.c_str(), input_stream)
            {

            }

            LexicalAnalysis::~LexicalAnalysis()
            {
                if (input_stream != stdin)
                    std::fclose(input_stream);
            }

            void LexicalAnalysis::consume_inline_comment()
            {
                while (true)
                {
                    std::uint32_t last = reader.read_one();

                    if (last == '\n' || last == util::Reader::END_OF_FILE)
                        break;
                }
            }

            void LexicalAnalysis::consume_integer_literal()
            {
                std::vector<std::uint8_t> lexeme;
                lexeme.emplace_back(reader.last_one());
                util::Location start(reader.get_location());

                while (true)
                {
                    std::uint32_t last = reader.read_one();

                    if (last < '0' || last > '9')
                        break;

                    lexeme.emplace_back((std::uint8_t) last);
                }

                pipeline->symbols_vector.emplace_back(Token::INT_LITERAL, lexeme, start.add_length(lexeme.size() - 1));
            }

            static inline Token calculate_alpha_numeric_token(const util::String& lexeme)
            {
                // Not the best possible implementation. Hope that the optimizer is good enough.


                if (lexeme == "none")
                    return Token::VOID_LITERAL;
                else if (lexeme == "true" || lexeme == "false")
                    return Token::BOOL_LITERAL;
                else if (lexeme == "null")
                    return Token::PTR_LITERAL;
                else if (lexeme == "arr")
                    return Token::ARR;
                else if (lexeme == "bool")
                    return Token::BOOL;
                else if (lexeme == "char")
                    return Token::CHAR;
                else if (lexeme == "del")
                    return Token::DEL;
                else if (lexeme == "do")
                    return Token::DO;
                else if (lexeme == "else")
                    return Token::ELSE;
                else if (lexeme == "end")
                    return Token::END;
                else if (lexeme == "fun")
                    return Token::FUN;
                else if (lexeme == "if")
                    return Token::IF;
                else if (lexeme == "int")
                    return Token::INT;
                else if (lexeme == "new")
                    return Token::NEW;
                else if (lexeme == "ptr")
                    return Token::PTR;
                else if (lexeme == "rec")
                    return Token::REC;
                else if (lexeme == "then")
                    return Token::THEN;
                else if (lexeme == "typ")
                    return Token::TYP;
                else if (lexeme == "var")
                    return Token::VAR;
                else if (lexeme == "void")
                    return Token::VOID;
                else if (lexeme == "where")
                    return Token::WHERE;
                else if (lexeme == "while")
                    return Token::WHILE;
                else
                    return Token::IDENTIFIER;

            }

            void LexicalAnalysis::consume_alpha_numeric()
            {
                std::vector<std::uint8_t> lexeme;
                lexeme.emplace_back(reader.last_one());
                util::Location start(reader.get_location());

                while (true)
                {
                    std::uint32_t last = reader.read_one();

                    bool valid =
                            ('a' <= last && last <= 'z') ||
                            ('A' <= last && last <= 'Z') ||
                            (last == '_') ||
                            ('0' <= last && last <= '9');

                    if (!valid)
                        break;

                    lexeme.emplace_back((std::uint8_t) last);
                }

                util::String lexeme_string(lexeme);
                Token token = calculate_alpha_numeric_token(lexeme_string);
                pipeline->symbols_vector.emplace_back(token, std::move(lexeme_string), start.add_length(lexeme.size() - 1));
            }

            bool LexicalAnalysis::consume_symbol()
            {
                auto inplace_append = [&] (const lexical_analysis::Token& token, util::String&& lexeme,
                                           util::Location&& location) -> bool
                    {
                        pipeline->symbols_vector.emplace_back(token, std::move(lexeme), std::move(location));
                        reader.read_one();
                        return false;
                    };

                auto consume_expected = [&] (std::uint32_t expected) -> bool
                    {
                        std::uint32_t next = reader.read_one();

                        if (next == expected)
                            return true;

                        reader.reuse_last();
                        return false;
                    };

                while (true)
                {
                    std::uint32_t last = reader.last_one();

                    if (last == util::Reader::END_OF_FILE)
                    {
                        reader.reuse_last();
                        return true;
                    }
                    else if (last == '\n')
                    {
                        return true;
                    }
                    else if (last == ' ' || last == '\t' || last == '\r')
                    {
                        reader.read_one();
                    }
                    else if (last == '#')
                    {
                        consume_inline_comment();
                    }
                    else if (('a' <= last && last <= 'z') || ('A' <= last && last <= 'Z') || last == '_')
                    {
                        consume_alpha_numeric();
                        return false;
                    }
                    else if ('0' <= last && last <= '9')
                    {
                        consume_integer_literal();
                        return false;
                    }
                    else if (last == '\'')
                    {
                        // TODO not implemented yet
                        InternalError::raise("lack of implementation for parsing char literals");
                        return false;
                    }
                    else if (last == '!')
                    {
                        if (consume_expected('='))
                            return inplace_append(Token::NEQ, "!=", reader.get_location());
                        else
                            return inplace_append(Token::NOT, "!", reader.get_location());
                    }
                    else if (last == '|')
                    {
                        return inplace_append(Token::OR, "|", reader.get_location());
                    }
                    else if (last == '^')
                    {
                        return inplace_append(Token::XOR, "^", reader.get_location());
                    }
                    else if (last == '&')
                    {
                        return inplace_append(Token::AND, "&", reader.get_location());
                    }
                    else if (last == '<')
                    {
                        if (consume_expected('='))
                            return inplace_append(Token::LEQ, "<=", reader.get_location());
                        else
                            return inplace_append(Token::LTH, "<", reader.get_location());
                    }
                    else if (last == '=')
                    {
                        if (consume_expected('='))
                            return inplace_append(Token::EQU, "==", reader.get_location());
                        else
                            return inplace_append(Token::ASSIGN, "=", reader.get_location());
                    }
                    else if (last == '>')
                    {
                        if (consume_expected('='))
                            return inplace_append(Token::GEQ, ">=", reader.get_location());
                        else
                            return inplace_append(Token::GTH, ">", reader.get_location());
                    }
                    else if (last == '+')
                    {
                        return inplace_append(Token::ADD, "+", reader.get_location());
                    }
                    else if (last == '-')
                    {
                        return inplace_append(Token::SUB, "-", reader.get_location());
                    }
                    else if (last == '*')
                    {
                        return inplace_append(Token::MUL, "*", reader.get_location());
                    }
                    else if (last == '/')
                    {
                        return inplace_append(Token::DIV, "/", reader.get_location());
                    }
                    else if (last == '%')
                    {
                        return inplace_append(Token::MOD, "%", reader.get_location());
                    }
                    else if (last == '$')
                    {
                        return inplace_append(Token::MEM, "$", reader.get_location());
                    }
                    else if (last == '@')
                    {
                        return inplace_append(Token::VAL, "@", reader.get_location());
                    }
                    else if (last == '.')
                    {
                        return inplace_append(Token::DOT, ".", reader.get_location());
                    }
                    else if (last == ',')
                    {
                        return inplace_append(Token::COMMA, ",", reader.get_location());
                    }
                    else if (last == ':')
                    {
                        return inplace_append(Token::COLON, ":", reader.get_location());
                    }
                    else if (last == ';')
                    {
                        return inplace_append(Token::SEMI_COLON, ";", reader.get_location());
                    }
                    else if (last == '(')
                    {
                        return inplace_append(Token::LEFT_PARENTHESIS, "(", reader.get_location());
                    }
                    else if (last == ')')
                    {
                        return inplace_append(Token::RIGHT_PARENTHESIS, ")", reader.get_location());
                    }
                    else if (last == '[')
                    {
                        return inplace_append(Token::LEFT_BRACKET, "[", reader.get_location());
                    }
                    else if (last == ']')
                    {
                        return inplace_append(Token::RIGHT_BRACKET, "]", reader.get_location());
                    }
                    else if (last == '{')
                    {
                        return inplace_append(Token::LEFT_BRACE, "{", reader.get_location());
                    }
                    else if (last == '}')
                    {
                        return inplace_append(Token::RIGHT_BRACE, "}", reader.get_location());
                    }
                    else
                    {
                        std::uint32_t printable = std::isprint(last) ? last : ' ';
                        CompileTimeError::raise(pipeline->file_name.c_str(), reader.get_location(),
                            util::String::format("unexpected read character: %lc (code: %ld)", printable, last));
                    }
                }
            }

            void LexicalAnalysis::consume_line()
            {
                reader.read_one(); // used to prepare the next character
                while (!consume_symbol());
            }

            void LexicalAnalysis::finalize_vector()
            {
                util::Location location(reader.get_line(), reader.get_column());
                pipeline->symbols_vector.emplace_back(Token::END_OF_FILE, nullptr, std::move(location));
            }

            void LexicalAnalysis::complete_0()
            {
                while (true)
                {
                    consume_line();

                    if (reader.read_one() == util::Reader::END_OF_FILE)
                        break;

                    reader.reuse_last();
                }

                finalize_vector();
            }
        }
    }
}
