#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include "SyntaticAnalysis.h"

// #define DEBUG

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
    m_lex(lex), m_current(lex.nextToken()) {

    }

SyntaticAnalysis::~SyntaticAnalysis() {

}

BlocksCommand* SyntaticAnalysis::start() {
    BlocksCommand* code = procCode();
    eat(TT_END_OF_FILE);
    return code;
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
    #ifdef DEBUG
    std::cout << "Expected (...," << tt2str(type) << "), " <<
                 "found (\"" << m_current.token << "\", " << tt2str(m_current.type) << ")" << std::endl;
    #endif

    if (type == m_current.type) {
        advance();
    }
    else {
        showError();
    }
}

//<code> ::= { <statement> }
BlocksCommand* SyntaticAnalysis::procCode() {
    BlocksCommand* code = new BlocksCommand(m_lex.line());

    while (m_current.type == TT_IF || m_current.type == TT_WHILE || m_current.type == TT_FOREACH || 
           m_current.type == TT_ECHO || m_current.type == TT_INCREMENT || m_current.type == TT_DECREMENT || 
           m_current.type == TT_VAR_VAR || m_current.type == TT_VAR || m_current.type == TT_OPEN_BRACES) {
        
        code->addCommand(procStatement());

    }

    return code;

}

//<statement> ::= <if> | <while> | <foreach> | <echo> | <assign>
Command* SyntaticAnalysis::procStatement() {

    switch (m_current.type) {
        case TT_IF:
            return procIf();
        case TT_WHILE:
            return procWhile();
        case TT_FOREACH:
            return procForeach();
        case TT_ECHO:
            return procEcho();
        default:
            return procAssign();
    }

}

//<if> ::= if '(' <boolexpr> ')' '{' <code> '}'
//         { elseif '(' <boolexpr> ')' '{' <code> '}' } [ else '{' <code> '}' ]
IfCommand* SyntaticAnalysis::procIf() {
    eat(TT_IF);

    eat(TT_OPEN_BRACES);
    BoolExpr* cond = procBoolexpr();
    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    Command* cmds = procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

    IfCommand* ifCommand = new IfCommand(m_lex.line(), cond, cmds);
    IfCommand *currentCommand = ifCommand, *newCommand;

    while (m_current.type == TT_ELSEIF) {
        eat(TT_ELSEIF);

        eat(TT_OPEN_BRACES);
        cond = procBoolexpr();
        eat(TT_CLOSE_BRACES);
        
        eat(TT_OPEN_CURLY_BRACKETS);
        cmds = procCode();
        eat(TT_CLOSE_CURLY_BRACKETS);

        newCommand = new IfCommand(m_lex.line(), cond, cmds);

        currentCommand->addElseCommands(newCommand);
        currentCommand = newCommand;
    }

    if (m_current.type == TT_ELSE) {
        eat(TT_ELSE);

        eat(TT_OPEN_CURLY_BRACKETS);
        cmds = procCode();
        eat(TT_CLOSE_CURLY_BRACKETS);

        currentCommand->addElseCommands(cmds);
    }

    return ifCommand;
}

//<while> ::= while '(' <boolexpr> ')' '{' <code> '}'
WhileCommand* SyntaticAnalysis::procWhile() {
    eat(TT_WHILE);

    eat(TT_OPEN_BRACES);
    BoolExpr* cond = procBoolexpr();
    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    Command* cmds = procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

    return new WhileCommand(m_lex.line(), cond, cmds);
}

//<foreach> ::= foreach '(' <expr> as <var> [ '=>' <var> ] ')' '{' <code> '}'
ForeachCommand* SyntaticAnalysis::procForeach() {
    eat(TT_FOREACH);  

    eat(TT_OPEN_BRACES);
    Expr* expr = procExpr();
    eat(TT_FOREACH_AS);
    
    Expr* key = procVarvar();

    Expr* value = 0;
    if (m_current.type == TT_ARRAY_ASSIGN) {
        eat(TT_ARRAY_ASSIGN);
        value = procVarvar();
    }

    eat(TT_CLOSE_BRACES);

    eat(TT_OPEN_CURLY_BRACKETS);
    Command* cmds = procCode();
    eat(TT_CLOSE_CURLY_BRACKETS);

    return new ForeachCommand(m_lex.line(), expr, cmds, (Variable*) key, (Variable*) value);
}

//<echo> ::= echo <expr> ';'
EchoCommand* SyntaticAnalysis::procEcho() {
    eat(TT_ECHO);

    Expr* expr = procExpr();
    EchoCommand* echoCmd = new EchoCommand(m_lex.line(), expr);

    eat(TT_SEMICOLON);

    return echoCmd;
}

//<assign> ::= <value> [ ('=' | '+=' | '-=' | '.=' | '*=' | '/=' | '%=') <expr> ] ';'
AssignCommand* SyntaticAnalysis::procAssign() {
    Expr* left = procValue();
    Expr* right;
    AssignOp op;

    switch (m_current.type) {
        case TT_ASSIGN:
            op = AssignOp::StdAssignOp;
            eat(TT_ASSIGN);
            break;
        case TT_ADD_ASSIGN:
            op = AssignOp::AddAssignOp;
            eat(TT_ADD_ASSIGN);
            break;
        case TT_SUB_ASSIGN:
            op = AssignOp::SubAssignOp;
            eat(TT_SUB_ASSIGN);
            break;
        case TT_CONCAT_ASSIGN:
            op = AssignOp::ConcatAssignOp;
            eat(TT_CONCAT_ASSIGN);
            break;
        case TT_MUL_ASSIGN:
            op = AssignOp::MulAssignOp;
            eat(TT_MUL_ASSIGN);
            break;
        case TT_DIV_ASSIGN:
            op = AssignOp::DivAssignOp;
            eat(TT_DIV_ASSIGN);
            break;
        case TT_MOD_ASSIGN:
            op = AssignOp::ModAssignOp;
            eat(TT_MOD_ASSIGN);
            break;
        default:
            eat(TT_SEMICOLON);
            return new AssignCommand(m_lex.line(), left, AssignOp::NoAssignOp);
    }
    
    right = procExpr();
    eat(TT_SEMICOLON);

    return new AssignCommand(m_lex.line(), left, op, right);
}

//<boolexpr> ::= [ '!' ] <cmpexpr> [ (and | or) <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBoolexpr() {
    bool notBool = false;
    BoolOp op;

    if (m_current.type == TT_NOT) {
        eat(TT_NOT);
        notBool = true;
    }

    BoolExpr* left = procCmpexpr();

    if (notBool) {
        left = new NotBoolExpr(m_lex.line(), left);
    }

    if (m_current.type == TT_AND || m_current.type == TT_OR) {
        if (m_current.type == TT_AND) op = BoolOp::And;
        else op = BoolOp::Or;

        eat(m_current.type);
        BoolExpr* right = procBoolexpr();

        return new CompositeBoolExpr(m_lex.line(), left, op, right);
    }

    return left;    

}

//<cmpexpr> ::= <expr> ('==' | '!=' | '<' | '>' | '<=' | '>=') <expr>
SingleBoolExpr* SyntaticAnalysis::procCmpexpr() {
    Expr* left = procExpr();

    RelOp op;
    switch (m_current.type) {
        case TT_EQUALS:
            op = RelOp::Equal;
            eat(TT_EQUALS);
            break;
        case TT_NOT_EQUALS:
            op = RelOp::NotEqual;
            eat(TT_NOT_EQUALS);
            break;
        case TT_LESSER:
            op = RelOp::LowerThan;
            eat(TT_LESSER);
            break;
        case TT_GREATER:
            op = RelOp::GreaterThan;
            eat(TT_GREATER);
            break;
        case TT_LESSER_EQUALS:
            op = RelOp::LowerEqual;
            eat(TT_LESSER_EQUALS);
            break;
        case TT_GREATER_EQUALS:
            op = RelOp::GreaterEqual;
            eat(TT_GREATER_EQUALS);
            break;          
        default:
            showError();
            break;
    }

    Expr* right = procExpr();

    return new SingleBoolExpr(m_lex.line(), left, op, right);
}

//<expr> ::= <term> { ('+' | '-' | '.') <term> }
Expr* SyntaticAnalysis::procExpr() {
    Expr* currentExpr = procTerm();
    BinaryOp op = BinaryOp::AddOp;

    while (m_current.type == TT_ADD || m_current.type == TT_SUB || m_current.type == TT_CONCAT) {
        switch (m_current.type) {
            case TT_ADD:
                op = BinaryOp::AddOp;
                break;
            case TT_SUB:
                op = BinaryOp::SubOp;
                break;
            case TT_CONCAT:
            default:
                op = BinaryOp::ConcatOp;
                break;
        }

        eat(m_current.type);

        currentExpr = new BinaryExpr(m_lex.line(), currentExpr, op, procTerm());
    }

    return currentExpr;
}

//<term> ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntaticAnalysis::procTerm() {
    Expr* currentExpr = procFactor();
  
    BinaryOp op = BinaryOp::AddOp;

    while (m_current.type == TT_MUL || m_current.type == TT_DIV || m_current.type == TT_MOD) {
        switch (m_current.type) {
            case TT_MUL:
                op = BinaryOp::MulOp;
                break;
            case TT_DIV:
                op = BinaryOp::DivOp;
                break;
            case TT_MOD:
            default:
                op = BinaryOp::ModOp;
                break;
        }      
        eat(m_current.type);        

        Expr* newExpr = procFactor();
        currentExpr = new BinaryExpr(m_lex.line(), currentExpr, op, newExpr);
    }

    return currentExpr;
}

//<factor> ::= <number> | <string> | <array> | <read> | <value>
Expr* SyntaticAnalysis::procFactor() {
    switch (m_current.type) {
        case TT_INTEGER: {
            IntegerValue* integerValue = new IntegerValue(std::stoi(m_current.token));

            eat(TT_INTEGER);
            return new ConstExpr(m_lex.line(), integerValue);
        }            
        case TT_STRING: {
            std::string string = m_current.token;
            string.erase(0, 1); string.erase(string.size()-1, 1); //Removes quotation marks
            StringValue* stringValue = new StringValue(string);

            eat(TT_STRING);
            return new ConstExpr(m_lex.line(), stringValue);
        }            
        case TT_ARRAY: {
            return procArray();     
        }                  
        case TT_READ: {
            return procRead();
        }            
        default: {
            return procValue();
        }            
    }

}

//<array> ::= array '(' [ <expr> '=>' <expr> { ',' <expr> '=>' <expr> } ] ')'
ArrayExpr* SyntaticAnalysis::procArray() {
    std::stringstream error;

    eat(TT_ARRAY);
    eat(TT_OPEN_BRACES);

    ArrayExpr* arrayExpr = new ArrayExpr(m_lex.line());

    Expr *key, *value;

    if (m_current.type != TT_CLOSE_BRACES) {
        key = procExpr();
        eat(TT_ARRAY_ASSIGN);
        value = procExpr();
        
        arrayExpr->insert(key, value);

        while (m_current.type != TT_CLOSE_BRACES) {
            eat(TT_COMMA);
            key = procExpr();
            eat(TT_ARRAY_ASSIGN);
            value = procExpr();

            arrayExpr->insert(key, value);   

        }
    }

    eat(TT_CLOSE_BRACES);
    
    return arrayExpr;
}

//<read> ::= read <expr>
ReadExpr* SyntaticAnalysis::procRead() {
    eat(TT_READ);
    Expr* expr = procExpr();
    return new ReadExpr(m_lex.line(), expr);
}

//<value> ::= [ ('++' | '—-') ] <access> | <access> [ ('++' | '--') ]
Expr* SyntaticAnalysis::procValue() {
    UnaryOp op;
    Expr* expr;
    if (m_current.type == TT_INCREMENT || m_current.type == TT_DECREMENT) {
        if (m_current.type == TT_INCREMENT) op = UnaryOp::PreIncOp;
        else op = UnaryOp::PreDecOp;

        eat(m_current.type);
        expr = procAccess();

        return new UnaryExpr(m_lex.line(), expr, op);
    }
    else {
        expr = procAccess();
        if (m_current.type == TT_INCREMENT || m_current.type == TT_DECREMENT) {
            if (m_current.type == TT_INCREMENT) op = UnaryOp::PosIncOp;
            else op = UnaryOp::PosDecOp;

            eat(m_current.type);

            return new UnaryExpr(m_lex.line(), expr, op);
        }

        return expr;
    }

}

//<access> ::= ( <varvar> | '(' <expr> ')' ) [ '[' <expr> ']' ]
AccessExpr* SyntaticAnalysis::procAccess() {
    Expr *base, *index;
    if (m_current.type == TT_VAR_VAR || m_current.type == TT_VAR) {
        base = procVarvar();
    }
    else {
        eat(TT_OPEN_BRACES);
        base = procExpr();
        eat(TT_CLOSE_BRACES);
    }

    if (m_current.type == TT_OPEN_BRACKETS) {
        eat(TT_OPEN_BRACKETS);
        index = procExpr();
        eat(TT_CLOSE_BRACKETS);
        return new AccessExpr(m_lex.line(), base, index);
    }

    return new AccessExpr(m_lex.line(), base);

}

//<varvar> ::= '$' <varvar> | <var>
Expr* SyntaticAnalysis::procVarvar() {
    if (m_current.type == TT_VAR_VAR) {
        eat(TT_VAR_VAR);    
        return new VarVarExpr(m_lex.line(), procVarvar());
    }
    else {
        return procVar();
    }
}

//<var>
Variable* SyntaticAnalysis::procVar() {
    std::string varName = m_current.token;
    varName.erase(0, 1); //Removes $

    Variable* var = new Variable(varName);
    eat(TT_VAR);
    return var;
}