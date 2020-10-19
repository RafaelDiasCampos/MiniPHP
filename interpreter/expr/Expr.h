#ifndef EXPR_H
#define EXPR_H

#include "../value/Type.h"

class Expr {
    public:
        enum ExprType {
            ConstExpr,
            ReadExpr,
            ArrayExpr,
            Variable,
            VarVarExpr,
            AccessExpr,
            UnaryExpr,
            BinaryExpr
        };

        Expr(int line, ExprType type): m_line(line), m_type(type) {}
        virtual ~Expr() {}

        int line() const {return m_line; }
        ExprType type() const {return m_type; }

    protected:
        int m_line;
        ExprType m_type;

};

#endif