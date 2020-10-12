#include "SymbolTable.h"

SymbolTable::SymbolTable() {

    //Symbols
    m_symbols[";"] = TT_SEMICOLON;
    m_symbols["("] = TT_OPEN_BRACES;
    m_symbols[")"] = TT_CLOSE_BRACES;
    m_symbols["["] = TT_OPEN_BRACKETS;
    m_symbols["]"] = TT_CLOSE_BRACKETS;
    m_symbols["{"] = TT_OPEN_CURLY_BRACKETS;
    m_symbols["}"] = TT_CLOSE_CURLY_BRACKETS;
    m_symbols[","] = TT_COMMA;

    //Commands
    m_symbols["if"] = TT_IF;
    m_symbols["else"] = TT_ELSE;
    m_symbols["elseif"] = TT_ELSEIF;
    m_symbols["while"] = TT_WHILE;
    m_symbols["foreach"] = TT_FOREACH;
    m_symbols["as"] = TT_FOREACH_AS;
    m_symbols["echo"] = TT_ECHO;

    //Values
    m_symbols["read"] = TT_READ;
    m_symbols["array"] = TT_ARRAY;

    //Operators
    m_symbols["+"] = TT_ADD;
    m_symbols["-"] = TT_SUB;
    m_symbols["*"] = TT_MUL;
    m_symbols["/"] = TT_DIV;
    m_symbols["%"] = TT_MOD;

    m_symbols["."] = TT_CONCAT;

    m_symbols["=="] = TT_EQUALS;
    m_symbols["!="] = TT_NOT_EQUALS;
    m_symbols["<"] = TT_LESSER;
    m_symbols[">"] = TT_GREATER;
    m_symbols["<="] = TT_LESSER_EQUALS;
    m_symbols[">="] = TT_GREATER_EQUALS;
    m_symbols["!"] = TT_NOT;

    m_symbols["and"] = TT_AND;
    m_symbols["or"] = TT_OR;
    
    m_symbols["="] = TT_ASSIGN;
    m_symbols["+="] = TT_ADD_ASSIGN;
    m_symbols["-="] = TT_SUB_ASSIGN;
    m_symbols["*="] = TT_MUL_ASSIGN;
    m_symbols["/="] = TT_DIV_ASSIGN;
    m_symbols["%="] = TT_MOD_ASSIGN;
    m_symbols[".="] = TT_CONCAT_ASSIGN;

    m_symbols["++"] = TT_INCREMENT;
    m_symbols["--"] = TT_DECREMENT;

    m_symbols["=>"] = TT_ARRAY_ASSIGN;

    //Variables
    m_symbols["$"] = TT_VAR_VAR;
}

SymbolTable::~SymbolTable() {

}

bool SymbolTable::contains(const std::string token) const {
    return m_symbols.find(token) != m_symbols.end();
}

enum TokenType SymbolTable::find(const std::string token) {
    return this->contains(token) ? m_symbols[token] : TT_INVALID_TOKEN;    
}