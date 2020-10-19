#include <sstream>
#include <iomanip>
#include "SingleBoolExpr.h"

SingleBoolExpr::SingleBoolExpr(int line, Expr* left, RelOp op, Expr* right) : BoolExpr(line, BoolExpr::SingleBoolExpr), m_left(left), m_op(op), m_right(right) {

}

SingleBoolExpr::~SingleBoolExpr() {

}

bool SingleBoolExpr::expr() {
    Type* typeLeft = ExprUtils::getExpr(m_left);
    Type* typeRight = ExprUtils::getExpr(m_right);

    IntegerValue *integerLeft, *integerRight;
    StringValue *stringLeft, *stringRight;

    if (typeLeft->type() == Type::ArrayType || typeRight->type() == Type::ArrayType) {
        std::stringstream error;
        error << std::setw(2) << std::setfill('0') << m_line << ": ";
        error << "Operacoes booleanas sao invalidas para arrays";
        throw error.str();
    }

    //Realiza comparacao com strings
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
            case Equal:
                return stringLeft->value().compare(stringRight->value()) == 0;
            case NotEqual:
                return stringLeft->value().compare(stringRight->value()) != 0;
            case LowerThan:
                return stringLeft->value().compare(stringRight->value()) > 0;
            case LowerEqual:
                return stringLeft->value().compare(stringRight->value()) >= 0;
            case GreaterThan:
                return stringLeft->value().compare(stringRight->value()) < 0;
            case GreaterEqual:
                return stringLeft->value().compare(stringRight->value()) <= 0;
        }
        
    }

    integerLeft = (IntegerValue*) typeLeft;
    integerRight = (IntegerValue*) typeRight;

    switch (m_op) {
        case Equal:
            return integerLeft->value() == integerRight->value();
        case NotEqual:
            return integerLeft->value() != integerRight->value();
        case LowerThan:
            return integerLeft->value() < integerRight->value();
        case LowerEqual:
            return integerLeft->value() <= integerRight->value();
        case GreaterThan:
            return integerLeft->value() > integerRight->value();
        case GreaterEqual:
        default:
            return integerLeft->value() >= integerRight->value();
    }  

    
}