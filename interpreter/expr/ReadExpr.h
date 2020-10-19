#ifndef READ_EXPR_H
#define READ_EXPR_H

#include "Expr.h"
#include "ExprUtils.h"
#include "../command/EchoCommand.h"

class ReadExpr : public Expr {
    public:
        ReadExpr(int line, Expr* msg);
        virtual ~ReadExpr();

        Type* expr();
        
    private:
        Expr* m_msg;
};

#endif