#include "CompositeBoolExpr.h"

CompositeBoolExpr::CompositeBoolExpr(int line, BoolExpr* left, BoolOp op, BoolExpr* right) : BoolExpr(line, BoolExpr::CompositeBoolExpr), m_left(left), m_op(op), m_right(right) {

}

CompositeBoolExpr::~CompositeBoolExpr() {

}

bool CompositeBoolExpr::expr() {
    switch (m_op) { 
        case And:
            return ExprUtils::getExpr(m_left) && ExprUtils::getExpr(m_right);
        case Or:
        default:
            return ExprUtils::getExpr(m_left) || ExprUtils::getExpr(m_right);
    }

}