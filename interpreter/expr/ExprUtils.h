#ifndef EXPR_UTILS_H
#define EXPR_UTILS_H

#include "Expr.h"
#include "ArrayExpr.h"
#include "BinaryExpr.h"
#include "ConstExpr.h"
#include "ReadExpr.h"
#include "UnaryExpr.h"
#include "VarVarExpr.h"
#include "Variable.h"
#include "AccessExpr.h"

#include "BoolExpr.h"
#include "SingleBoolExpr.h"
#include "NotBoolExpr.h"
#include "CompositeBoolExpr.h"

class ExprUtils {
    public:
        static Type* getExpr(Expr* expr);
        static bool getExpr(BoolExpr* expr);
};

#endif