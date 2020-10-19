#include <sstream>
#include <iomanip>
#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(int line, Expr* left, BinaryOp op, Expr* right) : Expr(line, Expr::BinaryExpr), m_left(left), m_op(op), m_right(right) {

}

BinaryExpr::~BinaryExpr() {

}

Type* BinaryExpr::expr() {
    std::stringstream error;

    Type* typeLeft = ExprUtils::getExpr(m_left);
    Type* typeRight = ExprUtils::getExpr(m_right);

    IntegerValue *integerLeft, *integerRight;
    StringValue *stringLeft, *stringRight;

    if (typeLeft->type() == Type::ArrayType || typeRight->type() == Type::ArrayType) {
        error << std::setw(2) << std::setfill('0') << m_line << ": ";
        error << "Operacoes binarias sao invalidas para arrays";
        throw error.str();
    }

    if (typeLeft->type() == Type::StringType || typeRight->type() == Type::StringType) {
        if (typeLeft->type() == Type::StringType) {
            stringLeft = (StringValue*) typeLeft;
        }
        else {
            integerLeft = (IntegerValue*) typeLeft;
            stringLeft = new StringValue(std::to_string(integerLeft->value()));
        }

        if (typeRight->type() == Type::StringType) {
            stringRight = (StringValue*) typeRight;
        }
        else {
            integerRight = (IntegerValue*) typeRight;
            stringRight = new StringValue(std::to_string(integerRight->value()));
        }

        switch (m_op) {
            case ConcatOp:
                return new StringValue(stringLeft->value() + stringRight->value());
            case AddOp:
            case SubOp:            
            case MulOp:
            case DivOp:
            case ModOp:
            default:
                error << std::setw(2) << std::setfill('0') << m_line << ": ";
                error << "Operacao binaria invalida para strings";
                throw error.str();
        }

    }

    integerLeft = (IntegerValue*) typeLeft;
    integerRight = (IntegerValue*) typeRight;

    switch (m_op) {
            case AddOp:
                return new IntegerValue(integerLeft->value() + integerRight->value());
            case SubOp:
                return new IntegerValue(integerLeft->value() - integerRight->value());
            case MulOp:
                return new IntegerValue(integerLeft->value() * integerRight->value());
            case DivOp:
                return new IntegerValue(integerLeft->value() / integerRight->value());
            case ModOp:
                return new IntegerValue(integerLeft->value() % integerRight->value());
            case ConcatOp:
            default:
                return new StringValue(std::to_string(integerLeft->value()) + std::to_string(integerRight->value()));
        }

}