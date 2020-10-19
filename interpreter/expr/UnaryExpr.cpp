#include <sstream>
#include <iomanip>
#include "UnaryExpr.h"

UnaryExpr::UnaryExpr(int line, Expr* expr, UnaryOp op) : Expr(line, Expr::UnaryExpr), m_expr(expr), m_op(op) {
}

UnaryExpr::~UnaryExpr() {

}

Type* UnaryExpr::expr() {
    std::stringstream error;

    Type* currentType = ExprUtils::getExpr(m_expr);
    Type* newType;
    int currentValue, newValue;

    switch (currentType->type()) {
        case Type::IntegerType:
            currentValue = ( (IntegerValue*) currentType)->value();
            break;
        case Type::ArrayType:        
        case Type::StringType:
        default:
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Operacoes binarias sao invalidas para strings e arrays.";
            throw error.str();
    }

    class VarVarExpr::VarVarExpr* varVarExpr;
    class Variable::Variable* variable;
    class AccessExpr::AccessExpr* accessExpr;

    switch (m_op) {
        case PreIncOp:
        case PosIncOp:
            newValue = currentValue + 1;
            break;         
        case PreDecOp:
        case PosDecOp:
        default:
            newValue = currentValue - 1;
            break;
    }

    newType = new IntegerValue(newValue);

    switch(m_expr->type()) {        
        case Expr::VarVarExpr:
            varVarExpr = (class VarVarExpr::VarVarExpr*) m_expr;
            varVarExpr->setExpr(newType);
            break;
        case Expr::Variable:
            variable = (class Variable::Variable*) m_expr;
            variable->setExpr(newType);
            break;
        case Expr::AccessExpr:
            accessExpr = (class AccessExpr::AccessExpr*) m_expr;
            accessExpr->setExpr(newType);
            break;
        default:
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Operacoes unarias sao invalidas para expressoes imutaveis.";
            throw error.str();
    }

    if (m_op == PreIncOp || m_op == PreDecOp) {
        return newType;
    }

    return currentType;
}