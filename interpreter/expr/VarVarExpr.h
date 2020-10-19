#ifndef VARVAR_EXPR_H
#define VARVAR_EXPR_H

#include "SetExpr.h"
#include "ExprUtils.h"
#include "Variable.h"
#include "../value/StringValue.h"

class VarVarExpr : public SetExpr {
    public:
        VarVarExpr(int line, Expr* varvar);
        virtual ~VarVarExpr();

        Type* expr();
        void setExpr(Type* type);
        
    private:
        std::string getVarName();
        Expr* m_varvar;
};

#endif