#ifndef BOOL_EXPR_H
#define BOOL_EXPR_H

class BoolExpr {
    public:
        enum BoolExprType {
            SingleBoolExpr,
            NotBoolExpr,
            CompositeBoolExpr
        };

        BoolExpr(int line, BoolExprType type): m_line(line), m_type(type) {}
        virtual ~BoolExpr() {}

        int line() const {return m_line; }
        BoolExprType type() {return m_type; }

    protected:
        int m_line;
        BoolExprType m_type;

};

#endif