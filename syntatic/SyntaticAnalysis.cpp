#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "SyntaticAnalysis.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(lex.nextToken()) {

    }

SyntaticAnalysis::~SyntaticAnalysis() {

}

void SyntaticAnalysis::start() {
    procCode();
    eat(TT_END_OF_FILE);
}

void SyntaticAnalysis::showError() {
    std::cout << std::setw(2) << std::setfill('0') << m_lex.line() << ": ";

    switch (m_current.type) {
        case TT_INVALID_TOKEN:
            std::cout << "Lexema invalido [" << m_current.token << "]" << std::endl;
            break;
        case TT_UNEXPECTED_EOF:
        case TT_END_OF_FILE:
            std::cout << "Fim de arquivo inesperado" << std::endl;
            break;
        default:
            std::cout << "Lexema nao esperado [" << m_current.token << "]" << std::endl;
            break;
    }

    exit(1);
 }

void SyntaticAnalysis::advance() {
    m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
    std::cout << "Expected (...," << tt2str(type) << "), " <<
                 "found (\"" << m_current.token << "\", " << tt2str(m_current.type) << ")" << std::endl;

    if (type == m_current.type) {
        advance();
    }
    else {
        showError();
    }
}

//<code> ::= { <statement> }
void SyntaticAnalysis::procCode() {
    while (m_current.type == TT_IF || m_current.type == TT_WHILE || m_current.type == TT_FOREACH || 
           m_current.type == TT_ECHO || m_current.type == TT_INCREMENT || m_current.type == TT_DECREMENT || 
           m_current.type == TT_VAR_VAR || m_current.type == TT_VAR || m_current.type == TT_OPEN_BRACES) {
        
        procStatement();

    }

}

//<statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
void SyntaticAnalysis::procStatement() {
    switch (m_current.type) {
        case TT_IF:
            procIf();
            break;
        case TT_WHILE:
            procWhile();
            break;
        case TT_FOREACH:
            procForeach();
            break;
        case TT_ECHO:
            procEcho();
            break;
        default:
            procAssign();
            break;
    }

}

//<if> ::= if '(' <boolexpr> ')' '{' <code> '}'
//         { elseif '(' <boolexpr> ')' '{' <code> '}' } [ else '{' <code> '}' ]
void SyntaticAnalysis::procIf() {
    eat(TT_IF);

    eat(TT_OPEN_BRACES);
    procBoolexpr();
    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

    while (m_current.type == TT_ELSEIF) {
        eat(TT_ELSEIF);

        eat(TT_OPEN_BRACES);
        procBoolexpr();
        eat(TT_CLOSE_BRACES);
        
        eat(TT_OPEN_CURLY_BRACKETS);
        procCode();
        eat(TT_CLOSE_CURLY_BRACKETS);
    }

    if (m_current.type == TT_ELSE) {
        eat(TT_ELSE);

        eat(TT_OPEN_CURLY_BRACKETS);
        procCode();
        eat(TT_CLOSE_CURLY_BRACKETS);
    }

}

//<while> ::= while '(' <boolexpr> ')' '{' <code> '}'
void SyntaticAnalysis::procWhile() {
    eat(TT_WHILE);

    eat(TT_OPEN_BRACES);
    procBoolexpr();
    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

}

//<foreach> ::= foreach '(' <expr> as <var> [ '=>' <var> ] ')' '{' <code> '}'
void SyntaticAnalysis::procForeach() {
    eat(TT_FOREACH);  

    eat(TT_OPEN_BRACES);
    procExpr();
    eat(TT_FOREACH_AS);
    eat(TT_VAR);

    if (m_current.type == TT_ARRAY_ASSIGN) {
        eat(TT_ARRAY_ASSIGN);
        eat(TT_VAR);
    }

    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

}

//<echo> ::= echo <expr> ';'
void SyntaticAnalysis::procEcho() {
    eat(TT_ECHO);
    procExpr();
    eat(TT_SEMICOLON);

}

//<assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
void SyntaticAnalysis::procAssign() {
    procValue();

    switch (m_current.type) {
        case TT_ASSIGN:
        case TT_ADD_ASSIGN:
        case TT_SUB_ASSIGN:
        case TT_CONCAT_ASSIGN:
        case TT_MUL_ASSIGN:
        case TT_DIV_ASSIGN:
        case TT_MOD_ASSIGN:
            eat(m_current.type);
            procExpr();
        default:
            eat(TT_SEMICOLON);
            break;
    }

}

//<boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
void SyntaticAnalysis::procBoolexpr() {
    if (m_current.type == TT_NOT) {
        eat(TT_NOT);
    }

    procCmpexpr();

    if (m_current.type == TT_AND || m_current.type == TT_OR) {
        eat(m_current.type);
        procBoolexpr();
    }

}

//<cmpexpr> ::= <expr> ('==' | '!=' | '<' | '>' | '<=' | '>=') <expr>
void SyntaticAnalysis::procCmpexpr() {
    procExpr();

    switch (m_current.type) {
        case TT_EQUALS:
        case TT_NOT_EQUALS:
        case TT_LESSER:
        case TT_GREATER:
        case TT_LESSER_EQUALS:
        case TT_GREATER_EQUALS:
            eat(m_current.type);
            break;
        default:
            showError();
            break;
    }

    procExpr();

}

//<expr> ::= <term> { ('+' | '-' | '.') <term> }
void SyntaticAnalysis::procExpr() {
    procTerm();
    
    while (m_current.type == TT_ADD || m_current.type == TT_SUB || m_current.type == TT_CONCAT) {
        eat(m_current.type);
        procTerm();
    }

}

//<term> ::= <factor> { ('*' | '/' | '%') <factor> }
void SyntaticAnalysis::procTerm() {
    procFactor();
     
    while (m_current.type == TT_MUL || m_current.type == TT_DIV || m_current.type == TT_MOD) {
        eat(m_current.type);
        procFactor();
    }

}

//<factor> ::= <number> | <string> | <array> | <read> | <value>
void SyntaticAnalysis::procFactor() {
    switch (m_current.type) {
        case TT_INTEGER:
        case TT_STRING:
            eat(m_current.type);
            break;
        case TT_ARRAY:
            procArray();
            break;
        case TT_READ:
            procRead();
            break;
        default:
            procValue();
            break;
    }

}

//<array> ::= array '(' [ <expr> '=>' <expr> { ',' <expr> '=>' <expr> } ] ')'
void SyntaticAnalysis::procArray() {
    eat(TT_ARRAY);
    eat(TT_OPEN_BRACES);

    if (m_current.type != TT_CLOSE_BRACES) {
        procExpr();
        eat(TT_ARRAY_ASSIGN);
        procExpr();

        while (m_current.type != TT_CLOSE_BRACES) {
            eat(TT_COMMA);
            procExpr();
            eat(TT_ARRAY_ASSIGN);
            procExpr();
        }
    }

    eat(TT_CLOSE_BRACES);

}

//<read> ::= read <expr>
void SyntaticAnalysis::procRead() {
    eat(TT_READ);
    procExpr();

}

//<value> ::= [ ('++' | '—-') ] <access> | <access> [ ('++' | '--') ]
void SyntaticAnalysis::procValue() {
    if (m_current.type == TT_INCREMENT || m_current.type == TT_DECREMENT) {
        eat(m_current.type);
        procAccess();
    }
    else {
        procAccess();
        if (m_current.type == TT_INCREMENT || m_current.type == TT_DECREMENT) {
            eat(m_current.type);
        }
    }

}

//<access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
void SyntaticAnalysis::procAccess() {
    if (m_current.type == TT_VAR_VAR || m_current.type == TT_VAR) {
        procVarvar();
    }
    else {
        eat(TT_OPEN_BRACES);
        procExpr();
        eat(TT_CLOSE_BRACES);
    }

    if (m_current.type == TT_OPEN_BRACKETS) {
        eat(TT_OPEN_BRACKETS);
        procExpr();
        eat(TT_CLOSE_BRACKETS);
    }

}

//<varvar> ::= '$' <varvar> | <var>
void SyntaticAnalysis::procVarvar() {    
    if (m_current.type == TT_VAR_VAR) {
        eat(TT_VAR_VAR);        
        procVarvar();
    }
    else {
        eat(TT_VAR);
    }
}