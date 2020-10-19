#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include "Expr.h"
#include "ExprUtils.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"

enum BinaryOp {
    AddOp = 1,
    SubOp,
    ConcatOp,
    MulOp,
    DivOp,
    ModOp
};

class BinaryExpr : public Expr {
    public:
        BinaryExpr(int line, Expr* left, BinaryOp op, Expr* right);
        virtual ~BinaryExpr();

        Type* expr();
        
    private:
        Expr *m_left;
        BinaryOp m_op;
        Expr *m_right;
};

#endif