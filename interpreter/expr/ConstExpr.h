#ifndef CONST_EXPR_H
#define CONST_EXPR_H

#include "Expr.h"

class ConstExpr : public Expr {
    public:
        ConstExpr(int line, Type* value);
        virtual ~ConstExpr();

        Type* expr();
        
    private:
        Type* m_value;
};

#endif