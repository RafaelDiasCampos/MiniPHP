#ifndef NOT_BOOL_EXPR_H
#define NOT_BOOL_EXPR_H

#include "BoolExpr.h"
#include "ExprUtils.h"

class NotBoolExpr : public BoolExpr {
    public:
        NotBoolExpr(int line, BoolExpr* expr);
        virtual ~NotBoolExpr();

        bool expr();
        
    private:
        BoolExpr* m_expr;
};

#endif