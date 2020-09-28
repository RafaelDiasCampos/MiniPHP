#include "LexicalAnalysis.h"

#include <iostream>

LexicalAnalysis::LexicalAnalysis(const char* filename) {
    m_input = fopen(filename, "r");
}

LexicalAnalysis::~LexicalAnalysis() {
    if (m_input != nullptr)
        fclose(m_input);
}

Lexeme LexicalAnalysis::nextToken() {    
    Lexeme lex;
    SymbolTable sb;

    int state = 1;

    while (state != 14 && state != 15 && state != 16 && state != 17 && state != 18) {
        int c = fgetc(m_input);

        //std::cout << state << std::endl;

        switch (state) {
            case 1: 
                switch(c) {
                    case -1:
                        state = 18;
                        lex.type = TT_END_OF_FILE;
                        break;
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case '{':
                    case '}':
                        state = 14;
                        lex.token += c;
                        break;
                    case '/':
                        state = 2;
                        lex.token += c;
                        break;
                    case '+':
                        state = 5;
                        lex.token += c;
                        break;
                    case '-':
                        state = 6;
                        lex.token += c;
                        break;
                    case '<':
                    case '>':
                    case '!':
                    case '*':
                    case '%':
                        state = 7;
                        lex.token += c;
                        break;
                    case '=':
                        state = 8;
                        lex.token += c;
                        break;
                    case '$':
                        state = 9;
                        lex.token += c;
                        break;
                    case '"':
                        state = 11;
                        lex.token += c;
                        break;
                    case '0':                    
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        state = 12;
                        lex.token += c;
                        break;
                    case ' ':
                    case '\n':
                    case '\t':
                        break;
                    default:
                        if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) {
                            state = 13;
                        }
                        else {
                            state = 14;
                        }
                        lex.token += c;
                }                
                break;
            case 2:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '=') {
                    state = 14;
                    lex.token += c;
                }
                else if (c == '*') {
                    state = 3;
                    lex.token += c;
                }
                else {
                    state = 14;
                    ungetc(c, m_input);
                }
                break;
            case 3:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '*') {
                    state = 4;
                }
            case 4:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '/') {
                    state = 1;
                    lex.token = "";
                }
                else {
                    state = 3;
                }
                break;
            case 5:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '+' || c == '=') {
                    state = 14;
                    lex.token += c;
                }
                else {
                    state = 14;
                    ungetc(c, m_input);
                }
                break;
            case 6:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '-' || c == '=') {
                    state = 14;
                    lex.token += c;
                }
                else {
                    state = 14;
                    ungetc(c, m_input);
                }
                break;
            case 7:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '=') {
                    state = 14;
                    lex.token += c;
                }
                else {
                    state = 14;
                    ungetc(c, m_input);
                }
                break;
            case 8:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                }
                else if (c == '=' || c == '>') {
                    state = 14;
                    lex.token += c;
                }
                else {
                    state = 14;
                    ungetc(c, m_input);
                }
                break;
            case 9:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '$') {
                    state = 14;
                    ungetc(c, m_input);
                }
                else if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) {
                    state = 10;
                    lex.token += c;
                }
                else {
                    lex.type = TT_INVALID_TOKEN;
                    state = 18;
                }
                break;
            case 10:
                if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) {
                    lex.token += c;
                }
                else {
                    state = 15;
                    ungetc(c, m_input);
                }
                break;
            case 11:
                if (c == -1) {
                    state = 18;
                    lex.type = TT_UNEXPECTED_EOF;
                    break;
                }
                else if (c == '"') {
                    state = 16;
                }
                lex.token += c;
                break;
            case 12:
                if (c >= '0' && c <= '9') {
                    lex.token += c;
                }
                else {
                    state = 17;
                    ungetc(c, m_input);
                }
                break;
            case 13:
                if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ) {
                    lex.token += c;
                }
                else {
                    state = 14;
                    ungetc(c, m_input);
                }
                break;
            default:
                throw std::string("Invalid State");
        }
    }

    switch (state) {
        case 14:
            lex.type = sb.find(lex.token);
            break;
        case 15:
            lex.type = TT_VAR;
            break;
        case 16:
            lex.type = TT_STRING;
            break;
        case 17:
            lex.type = TT_INTEGER;
            break;
    }

    return lex;
}