#include "LexicalAnalysis.h"

LexicalAnalysis::LexicalAnalysis(const char* filename) {
    m_input = fopen(filename, "r");
}

LexicalAnalysis::~LexicalAnalysis() {
    if (m_input != nullptr)
        fclose(m_input);
}

int LexicalAnalysis::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int LexicalAnalysis::isDigit(char c) {
    return c >= '0' && c <= '9';
}

Lexeme LexicalAnalysis::nextToken() {    
    Lexeme lex;
    SymbolTable sb;

    int state = 1;

    while (state != 15 && state != 16) {
        int c = fgetc(m_input);

        switch (state) {            
            case 1:
                switch (c) {
                    case -1:
                        lex.type = TT_END_OF_FILE;
                        state = 16;
                        break;
                    case '\t':
                    case '\r':
                    case '\n':
                    case ' ':
                        break;
                    case '/':
                        lex.token += c;
                        state = 2;
                        break;
                    case '+':
                        lex.token += c;
                        state = 5;
                        break;
                    case '-':
                        lex.token += c;
                        state = 6;
                        break;
                    case '.':
                    case '*':
                    case '%':
                    case '!':
                    case '<':
                    case '>':
                        lex.token += c;
                        state = 7;
                        break;
                    case '=':
                        lex.token += c;
                        state = 8;
                        break;
                    case '(':
                    case ')':
                    case '{':
                    case '}':
                    case ';':
                    case ',':
                    case '[':
                    case ']':
                        lex.token += c;
                        state = 15;
                        break;
                    case '$':
                        lex.token += c;
                        state = 10;
                        break;
                    case '"':
                        lex.token += c;
                        state = 13;
                        break;
                    default:
                        if (isLetter(c)) {
                            lex.token += c;
                            state = 9;
                        }
                        else if (isDigit(c)) {
                            lex.token += c;
                            state = 12;
                        }
                        else {
                            lex.token += c;
                            lex.type = TT_INVALID_TOKEN;
                            state = 16;
                        }
                        break;
                }
                break;
            case 2:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (c == '*') {
                    state = 3;
                }
                else {
                    ungetc(c, m_input);
                    state = 15;
                }
                break;
            case 3:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (c == '*') {
                    state = 4;
                }
                break;
            case 4:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (c == '/') {
                    lex.token = "";
                    state = 1;
                }
                else {
                    lex.token += c;
                    state = 15;
                }
                break;
            case 5:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (c == '+' || c == '=') {
                    lex.token += c;
                    state = 15;
                }
                else {
                    ungetc(c, m_input);
                    state = 15;
                }
                break;
            case 6:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (c == '-' || c == '=') {
                    lex.token += c;
                    state = 15;
                }
                else {
                    ungetc(c, m_input);
                    state = 15;
                }
                break;
            case 7:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (c == '=') {
                    lex.token += c;
                    state = 15;
                }
                else {
                    ungetc(c, m_input);
                    state = 15;
                }
                break;
            case 8:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (c == '>' || c == '=') {
                    lex.token += c;
                    state = 15;
                }
                else {
                    ungetc(c, m_input);
                    state = 15;
                }
                break;
            case 9:
                if (c == -1) {
                    state = 15;
                }
                else if (isLetter(c)) {
                    lex.token += c;
                }
                else {
                    ungetc(c, m_input);
                    state = 15;
                }
                break;
            case 10:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 15;
                }
                else if (isLetter(c)) {
                    lex.token += c;
                    state = 11;
                }
                else {
                    ungetc(c, m_input);
                    state = 15;
                }
                break;
            case 11:
                if (c == -1) {
                    lex.type = TT_VAR;
                    state = 16;
                }
                else if (isLetter(c) || isDigit(c)) {
                    lex.token += c;
                }
                else {
                    ungetc(c, m_input);
                    lex.type = TT_VAR;
                    state = 16;
                }
                break;
            case 12:
                if (c == -1) {
                    lex.type = TT_INTEGER;
                    state = 16;
                }
                else if (isDigit(c)) {
                    lex.token += c;
                }
                else {
                    ungetc(c, m_input);
                    lex.type = TT_INTEGER;
                    state = 16;
                }
                break;
            case 13:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 16;
                }
                else if (c == '\\') {
                    lex.token += c;
                    state = 14;
                }
                else if (c == '"') {
                    lex.token += c;
                    lex.type = TT_STRING;
                    state = 16;
                }
                else {
                    lex.token += c;
                }
                break;
            case 14:
                if (c == -1) {
                    lex.type = TT_UNEXPECTED_EOF;
                    state = 16;
                }
                else if (c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't' || c == '\\' || c == '"') {
                    lex.token += c;
                    state = 13;
                }
                else {
                    lex.token += c;
                    lex.type = TT_INVALID_TOKEN;
                    state = 16;
                }
                break;
            default:
                throw std::string("Invalid State");
        }
    }

    if (state == 15) {
        lex.type = sb.find(lex.token);
    }

    return lex;
}