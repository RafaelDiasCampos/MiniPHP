#ifndef ARRAY_EXPR_H
#define ARRAY_EXPR_H

#include "Expr.h"
#include "ExprUtils.h"
#include <map>


class ArrayExpr : public Expr {
    public:
        ArrayExpr(int line);
        virtual ~ArrayExpr();

        Type* expr();
        void insert(Expr* key, Expr* value);
        
    private:
        std::map<Expr*, Expr*> m_array;
};

#endif