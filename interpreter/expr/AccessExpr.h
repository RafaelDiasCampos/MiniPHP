#ifndef ACCESS_EXPR_H
#define ACCESS_EXPR_H

#include "VarVarExpr.h"
#include "Variable.h"
#include "ExprUtils.h"
#include "SetExpr.h"
#include "../value/ArrayValue.h"
#include "../value/IntegerValue.h"
#include "../value/StringValue.h"

class AccessExpr : public SetExpr {
    public:
        AccessExpr(int line, Expr* base, Expr* index = 0);
        virtual ~AccessExpr();

        Type* expr();
        void setExpr(Type* value);
        
    private:
        Expr* m_base;
        Expr* m_index;
};

#endif