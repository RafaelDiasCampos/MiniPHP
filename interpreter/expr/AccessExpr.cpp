#include <sstream>
#include <iomanip>
#include "AccessExpr.h"

AccessExpr::AccessExpr(int line, Expr* base, Expr* index) : SetExpr(line, Expr::AccessExpr), m_base(base), m_index(index) {

}

AccessExpr::~AccessExpr() {

}

Type* AccessExpr::expr() {
    std::stringstream error;

    Type* typeBase = ExprUtils::getExpr(m_base);

    if (typeBase->type() != Type::ArrayType) { 
        if (m_index) {
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Nao e possivel utilizar indice para acessar tipos diferentes de array";
            throw error.str();
        }
        return typeBase;
    }

    if (!m_index) {
        return typeBase;
    }

    auto array = ( (ArrayValue*) typeBase)->value();

    Type* typeIndex = ExprUtils::getExpr(m_index);
    std::string stringIndex;

    switch (typeIndex->type()) {
        case Type::IntegerType:
            stringIndex = std::to_string(( (IntegerValue*) typeIndex)->value());
            break;
        case Type::StringType:
            stringIndex = ( (StringValue*) typeIndex)->value();
            break;
        case Type::ArrayType:
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "O indice nao pode ser um array";
            throw error.str();
    }

    auto element = array.find(stringIndex);

    if (element != array.end()) {
        return element->second;
    }

    return new IntegerValue(0);
}

void AccessExpr::setExpr(Type* value) {
    std::stringstream error;

    class VarVarExpr::VarVarExpr* varVarExpr;
    class Variable::Variable* variable;
    class AccessExpr::AccessExpr* accessExpr;

    switch(m_base->type()) {        
        case Expr::VarVarExpr:
            varVarExpr = (class VarVarExpr::VarVarExpr*) m_base;
            varVarExpr->setExpr(value);
            return;
        case Expr::Variable:
            variable = (class Variable::Variable*) m_base;
            variable->setExpr(value);
            return;
        case Expr::AccessExpr:
            accessExpr = (class AccessExpr::AccessExpr*) m_base;
            accessExpr->setExpr(value);
            return;
        default:
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Operacoes de atribuicao sao invalidas para expressoes imutaveis";
            throw error.str();
    }

}