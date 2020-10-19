#include "NotBoolExpr.h"

NotBoolExpr::NotBoolExpr(int line, BoolExpr* expr) : BoolExpr(line, BoolExpr::NotBoolExpr), m_expr(expr) {

}

NotBoolExpr::~NotBoolExpr() {

}

bool NotBoolExpr::expr() {
    return !ExprUtils::getExpr(m_expr);
}