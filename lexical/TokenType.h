#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>

enum TokenType {
    //Specials
    TT_UNEXPECTED_EOF = -2,
    TT_INVALID_TOKEN = -1,
    TT_END_OF_FILE = 0,

    //Symbols
    TT_SEMICOLON,             // ;
    TT_OPEN_BRACES,           // (
    TT_CLOSE_BRACES,          // )
    TT_OPEN_BRACKETS,         // [
    TT_CLOSE_BRACKETS,        // ]
    TT_OPEN_CURLY_BRACKETS,   // {
    TT_CLOSE_CURLY_BRACKETS,  // }
    TT_COMMA,                 // ,

    //Commands
    TT_IF,
    TT_ELSE,
    TT_ELSEIF,
    TT_WHILE,
    TT_FOREACH,
    TT_FOREACH_AS,
    TT_ECHO,

    //Constants
    TT_INTEGER, 
    TT_STRING,
    TT_LOGIC,

    //Values
    TT_READ,
    TT_ARRAY,

    //Operators
    TT_ADD,              // +
    TT_SUB,              // -
    TT_MUL,              // *
    TT_DIV,              // /
    TT_MOD,              // %

    TT_CONCAT,           // .

    TT_EQUALS,           // ==
    TT_NOT_EQUALS,       // !=
    TT_LESSER,           // <
    TT_GREATER,          // >
    TT_LESSER_EQUALS,    // <=
    TT_GREATER_EQUALS,   // >=
    TT_NOT,              // !

    TT_AND,              // and
    TT_OR,               // or
    
    TT_ASSIGN,           // =
    TT_ADD_ASSIGN,       // +=
    TT_SUB_ASSIGN,       // -=
    TT_MUL_ASSIGN,       // *=
    TT_DIV_ASSIGN,       // /=
    TT_MOD_ASSIGN,       // %=
    TT_CONCAT_ASSIGN,    // .=

    TT_INCREMENT,        // ++
    TT_DECREMENT,        // --

    TT_ARRAY_ASSIGN,     // =>

    //Variables
    TT_VAR,
    TT_VAR_VAR           // $
};

inline std::string tt2str(enum TokenType type) {

    switch (type) {
        //Specials
        case TT_UNEXPECTED_EOF:
            return "UNEXPECTED_EOF";
        case TT_INVALID_TOKEN:
            return "INVALID_TOKEN";
        case TT_END_OF_FILE:
            return "END_OF_FILE";

        //Symbols
        case TT_SEMICOLON:
            return "SEMICOLON";
        case TT_OPEN_BRACES:
            return "OPEN_BRACES";
        case TT_CLOSE_BRACES:
            return "CLOSE_BRACES";
        case TT_OPEN_BRACKETS:
            return "OPEN_BRACKET";
        case TT_CLOSE_BRACKETS:
            return "CLOSE_BRACKET";
        case TT_OPEN_CURLY_BRACKETS:
            return "OPEN_CURLY_BRACKETS";
        case TT_CLOSE_CURLY_BRACKETS:
            return "CLOSE_CURLY_BRACKETS";
        case TT_COMMA:
            return "COMMA";

        //Commands
        case TT_IF:
            return "IF";
        case TT_ELSE:
            return "ELSE";
        case TT_ELSEIF:
            return "ELSEIF";
        case TT_WHILE:
            return "WHILE";
        case TT_FOREACH:
            return "FOREACH";
        case TT_FOREACH_AS:
            return "FOREACH_AS";
        case TT_ECHO:
            return "ECHO";

        //Constants
        case TT_INTEGER: 
            return "INTEGER";
        case TT_STRING:
            return "STRING";
        case TT_LOGIC:
            return "LOGIC";

        //Values
        case TT_READ:
            return "READ";
        case TT_ARRAY:
            return "ARRAY";

        //Operators
        case TT_ADD:
            return "ADD";
        case TT_SUB:
            return "SUB";
        case TT_MUL:
            return "MUL";
        case TT_DIV:
            return "DIV";
        case TT_MOD:
            return "MOD";

        case TT_CONCAT:
            return "CONCAT";

        case TT_EQUALS:
            return "EQUALS";
        case TT_NOT_EQUALS:
            return "NOT_EQUALS";
        case TT_LESSER:
            return "LESSER";
        case TT_GREATER:
            return "GREATER";
        case TT_LESSER_EQUALS:
            return "LESSER_EQUALS";
        case TT_GREATER_EQUALS:
            return "GREATER_EQUALS";
        case TT_NOT:
            return "NOT";

        case TT_AND:
            return "AND";
        case TT_OR:
            return "OR";
        
        case TT_ASSIGN:
            return "ASSIGN";
        case TT_ADD_ASSIGN:
            return "ADD_ASSIGN";
        case TT_SUB_ASSIGN:
            return "SUB_ASSIGN";
        case TT_MUL_ASSIGN:
            return "MUL_ASSIGN";
        case TT_DIV_ASSIGN:
            return "DIV_ASSIGN";
        case TT_MOD_ASSIGN:
            return "MOD_ASSIGN";
        case TT_CONCAT_ASSIGN:
            return "CONCAT_ASSIGN";

        case TT_INCREMENT:
            return "INCREMENT";
        case TT_DECREMENT:
            return "DECREMENT";

        case TT_ARRAY_ASSIGN:
            return "ARRAY_ASSIGN";

        //Variables
        case TT_VAR:
            return "VAR";
        case TT_VAR_VAR:
            return "VAR_VAR";

        default:
            return "NON_EXISTENT_TOKEN";
    };

}

#endif