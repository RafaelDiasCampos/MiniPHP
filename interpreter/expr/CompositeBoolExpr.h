#ifndef COMPOSITE_BOOL_EXPR_H
#define COMPOSITE_BOOL_EXPR_H

#include "BoolExpr.h"
#include "ExprUtils.h"

enum BoolOp {
    And = 1,
    Or
};

class CompositeBoolExpr : public BoolExpr {
    public:
        CompositeBoolExpr(int line, BoolExpr* left, BoolOp op, BoolExpr* right);
        virtual ~CompositeBoolExpr();

        bool expr();
        
    private:
        BoolExpr *m_left;
        BoolOp m_op;
        BoolExpr *m_right;
};

#endif