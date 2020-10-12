#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

class SyntaticAnalysis {
    public:
        SyntaticAnalysis(LexicalAnalysis& lex);
        virtual ~SyntaticAnalysis();

        void start();
    private:
        LexicalAnalysis& m_lex;
        Lexeme m_current;

        void advance();
        void eat(enum TokenType type);
        void showError();

        void procCode();
        void procStatement();
        void procIf();
        void procWhile();
        void procForeach();
        void procEcho();
        void procAssign();
        void procBoolexpr();
        void procCmpexpr();
        void procExpr();
        void procTerm();
        void procFactor();
        void procArray();
        void procRead();
        void procValue();
        void procAccess();
        void procVarvar();
};

#endif