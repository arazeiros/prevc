
#ifndef PREVC_PIPELINE_LEXICALANALYSIS_TOKEN_HXX
#define PREVC_PIPELINE_LEXICALANALYSIS_TOKEN_HXX

#include <prevc/error.hxx>

namespace prevc
{
    namespace pipeline
    {
        namespace lexical_analysis
        {
            /**
             * \brief Token representation in lexical analysis pipeline.
             * */
            enum class Token
            {
                OR,
                XOR,
                AND,

                EQU,
                NEQ,
                LTH,
                GTH,
                LEQ,
                GEQ,

                ADD,
                SUB,
                MUL,
                DIV,
                MOD,

                NOT,
                MEM,
                VAL,
                NEW,
                DEL,

                ASSIGN,
                COLON,
                COMMA,
                DOT,
                SEMI_COLON,

                LEFT_BRACE,
                RIGHT_BRACE,
                LEFT_BRACKET,
                RIGHT_BRACKET,
                LEFT_PARENTHESIS,
                RIGHT_PARENTHESIS,

                VOID_LITERAL,
                BOOL_LITERAL,
                CHAR_LITERAL,
                INT_LITERAL,
                PTR_LITERAL,

                VOID,
                BOOL,
                CHAR,
                INT,
                PTR,
                ARR,
                REC,

                DO,
                ELSE,
                END,
                FUN,
                IF,
                THEN,
                TYP,
                VAR,
                WHERE,
                WHILE,

                IDENTIFIER,

                END_OF_FILE
            };

            /**
             * \brief Returns the C-string representation of a specified token.
             * \param token The specified token.
             * \return The C-string representation.
             * */
            constexpr static const char* to_string(Token token)
            {
                switch (token)
                {
                    case Token::OR:                return "OR";
                    case Token::XOR:               return "XOR";
                    case Token::AND:               return "AND";

                    case Token::EQU:               return "EQU";
                    case Token::NEQ:               return "NEQ";
                    case Token::LTH:               return "LTH";
                    case Token::GTH:               return "GTH";
                    case Token::LEQ:               return "LEQ";
                    case Token::GEQ:               return "GEQ";

                    case Token::ADD:               return "ADD";
                    case Token::SUB:               return "SUB";
                    case Token::MUL:               return "MUL";
                    case Token::DIV:               return "DIV";
                    case Token::MOD:               return "MOD";

                    case Token::NOT:               return "NOT";
                    case Token::MEM:               return "MEM";
                    case Token::VAL:               return "VAL";
                    case Token::NEW:               return "NEW";
                    case Token::DEL:               return "DEL";

                    case Token::ASSIGN:            return "ASSIGN";
                    case Token::COLON:             return "COLON";
                    case Token::COMMA:             return "COMMA";
                    case Token::DOT:               return "DOT";
                    case Token::SEMI_COLON:        return "SEMI_COLON";

                    case Token::LEFT_BRACE:        return "LEFT_BRACE";
                    case Token::RIGHT_BRACE:       return "RIGHT_BRACE";
                    case Token::LEFT_BRACKET:      return "LEFT_BRACKET";
                    case Token::RIGHT_BRACKET:     return "RIGHT_BRACKET";
                    case Token::LEFT_PARENTHESIS:  return "LEFT_PARENTHESIS";
                    case Token::RIGHT_PARENTHESIS: return "RIGHT_PARENTHESIS";

                    case Token::VOID_LITERAL:      return "VOID_LITERAL";
                    case Token::BOOL_LITERAL:      return "BOOL_LITERAL";
                    case Token::CHAR_LITERAL:      return "CHAR_LITERAL";
                    case Token::INT_LITERAL:       return "INT_LITERAL";
                    case Token::PTR_LITERAL:       return "PTR_LITERAL";

                    case Token::VOID:              return "VOID";
                    case Token::BOOL:              return "BOOL";
                    case Token::CHAR:              return "CHAR";
                    case Token::INT:               return "INT";
                    case Token::PTR:               return "PTR";
                    case Token::ARR:               return "ARR";
                    case Token::REC:               return "REC";

                    case Token::DO:                return "DO";
                    case Token::ELSE:              return "ELSE";
                    case Token::END:               return "END";
                    case Token::FUN:               return "FUN";
                    case Token::IF:                return "IF";
                    case Token::THEN:              return "THEN";
                    case Token::TYP:               return "TYP";
                    case Token::VAR:               return "VAR";
                    case Token::WHERE:             return "WHERE";
                    case Token::WHILE:             return "WHILE";

                    case Token::IDENTIFIER:        return "IDENTIFIER";

                    case Token::END_OF_FILE:       return "END_OF_FILE";

                    default:
                        prevc::InternalError::raise("token not recognized");
                }
            }
        }
    }
}

#endif
