#ifndef LEXEME_H
#define LEXEME_H

#include <sstream>
#include "TokenType.h"

struct Lexeme {
    std::string token;
    enum TokenType type;

    Lexeme() : token(""), type(TT_END_OF_FILE) {}
    virtual ~Lexeme () {}

    const std::string str() {
        std::stringstream ss;

        ss << "(\"" << token << "\", " << tt2str(type) << ")";
        return ss.str();
    }
};

#endif