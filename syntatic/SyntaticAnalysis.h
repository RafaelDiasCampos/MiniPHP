#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"
#include "InterpreterDependencies.h"
#include <string>

class SyntaticAnalysis {
    public:
        SyntaticAnalysis(LexicalAnalysis& lex);
        virtual ~SyntaticAnalysis();

        BlocksCommand* start();
    private:
        LexicalAnalysis& m_lex;
        Lexeme m_current;

        void advance();
        void eat(enum TokenType type);
        void showError();

        BlocksCommand* procCode();
        Command* procStatement();
        IfCommand* procIf();
        WhileCommand* procWhile();
        ForeachCommand* procForeach();
        EchoCommand* procEcho();
        AssignCommand* procAssign();
        BoolExpr* procBoolexpr();
        SingleBoolExpr* procCmpexpr();
        Expr* procExpr();
        Expr* procTerm();
        Expr* procFactor();
        ArrayExpr* procArray();
        ReadExpr* procRead();
        Expr* procValue();
        AccessExpr* procAccess();
        Expr* procVarvar();
        Variable* procVar();
};

#endif