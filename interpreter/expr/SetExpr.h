#ifndef SET_EXPR_H
#define SET_EXPR_H

#include "Expr.h"

class SetExpr : public Expr {
    public:
        SetExpr(int line, Expr::ExprType type) : Expr(line, type) {}
        virtual ~SetExpr() {}
        
        void setExpr(Type* value);
        
    protected:
        Type* m_value;
};

#endif