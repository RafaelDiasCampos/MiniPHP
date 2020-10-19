#include <sstream>
#include <iomanip>
#include "VarVarExpr.h"

VarVarExpr::VarVarExpr(int line, Expr* varvar) : SetExpr(line, Expr::VarVarExpr), m_varvar(varvar) {

}

VarVarExpr::~VarVarExpr() {

}

std::string VarVarExpr::getVarName() {
    Type* varType = ExprUtils::getExpr(m_varvar);
    std::string varName; 

    switch(varType->type()) {        
        case Type::IntegerType:
            varName = std::to_string( ( (IntegerValue*) varType )->value());
            break;
        case Type::StringType:
            varName = ( (StringValue*) varType )->value();
            break;
        case Type::ArrayType:
            std::stringstream error;
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Expressoes VarVar sao invalidas para arrays.";
            throw error.str();
    }

    return varName;
}

Type* VarVarExpr::expr() {    
    class Variable::Variable* var = new class Variable::Variable(getVarName());

    return ExprUtils::getExpr(var);
}

void VarVarExpr::setExpr(Type* type) {
    class Variable::Variable* var = new class Variable::Variable(getVarName());

    var->setExpr(type);
}