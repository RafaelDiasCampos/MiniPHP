#ifndef SINGLE_BOOL_EXPR_H
#define SINGLE_BOOL_EXPR_H

#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "BoolExpr.h"
#include "Expr.h"
#include "ExprUtils.h"

enum RelOp {
    Equal = 1,
    NotEqual,
    LowerThan,
    LowerEqual,
    GreaterThan,
    GreaterEqual
};

class SingleBoolExpr : public BoolExpr {
    public:
        SingleBoolExpr(int line, Expr* left, RelOp op, Expr* right);
        virtual ~SingleBoolExpr();

        bool expr();
        
    private:
        Expr *m_left;
        RelOp m_op;
        Expr *m_right;
};

#endif