#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H

enum UnaryOp {
    PreIncOp = 1,
    PreDecOp,
    PosIncOp,
    PosDecOp
};

#include "Expr.h"
#include "ExprUtils.h"
#include "VarVarExpr.h"
#include "Variable.h"
#include "AccessExpr.h"

class UnaryExpr : public Expr {
    public:
        UnaryExpr(int line, Expr* expr, UnaryOp op);
        virtual ~UnaryExpr();

        Type* expr();
        
    private:        
        Expr* m_expr;
        UnaryOp m_op;
};


#endif