#include <sstream>
#include <iomanip>
#include "AssignCommand.h"

AssignCommand::AssignCommand(int line, Expr* left, AssignOp op, Expr* right) : Command(line), m_left(left), m_op(op), m_right(right) {

}

AssignCommand::~AssignCommand() {

}

void AssignCommand::execute() {
    std::stringstream error;

    Type* typeLeft = ExprUtils::getExpr(m_left);

    if (!m_right) {
        return;
    }

    Type* typeRight = ExprUtils::getExpr(m_right);

    IntegerValue *integerLeft, *integerRight;
    StringValue *stringLeft, *stringRight;

    VarVarExpr* varVarExpr;
    Variable* variable;
    AccessExpr* accessExpr;

    std::string newStringValue;
    int newIntValue;

    if (typeRight->type() == Type::ArrayType) {

        if (m_op == AssignOp::NoAssignOp) {
            return;
        }
        else if (m_op != AssignOp::StdAssignOp) {            
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Operacao de atribuicao utilizada invalida para arrays";
            throw error.str();
        }

        switch(m_left->type()) {      
            case Expr::VarVarExpr:
                varVarExpr = (VarVarExpr*) m_left;
                varVarExpr->setExpr(typeRight);
                return;
            case Expr::Variable:
                variable = (Variable*) m_left;
                variable->setExpr(typeRight);
                return;
            case Expr::AccessExpr:
                accessExpr = (AccessExpr*) m_left;
                accessExpr->setExpr(typeRight);
                return;
            default:
                error << std::setw(2) << std::setfill('0') << m_line << ": ";
                error << "Operacoes de atribuicao sao invalidas para expressoes imutaveis";
                throw error.str();
        }
    }

    //Realiza atribuicao com strings
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
            case NoAssignOp:
                return;
            case StdAssignOp:
                newStringValue = stringRight->value();
                break;    
            case ConcatAssignOp:
                newStringValue = stringLeft->value() + stringRight->value();
                break;
            case AddAssignOp:                
            case SubAssignOp:                
            case MulAssignOp:                
            case DivAssignOp:                
            case ModAssignOp:
            default:
                error << std::setw(2) << std::setfill('0') << m_line << ": ";
                error << "Operacao de atribuicao utilizada invalida para strings";
                throw error.str();              
        }

        StringValue* strValue = new StringValue(newStringValue);

        switch(m_left->type()) {        
            case Expr::VarVarExpr:
                varVarExpr = (VarVarExpr*) m_left;
                varVarExpr->setExpr(strValue);
                return;
            case Expr::Variable:
                variable = (Variable*) m_left;
                variable->setExpr(strValue);
                return;
            case Expr::AccessExpr:
                accessExpr = (AccessExpr*) m_left;
                accessExpr->setExpr(strValue);
                return;
            default:
                error << std::setw(2) << std::setfill('0') << m_line << ": ";
                error << "Operacoes de atribuicao sao invalidas para expressoes imutaveis";
                throw error.str();
        }
        
    }

    integerLeft = (IntegerValue*) typeLeft;
    integerRight = (IntegerValue*) typeRight;

    switch (m_op) {
        case NoAssignOp:
            return;
        case StdAssignOp:
            newIntValue = integerRight->value();
            break;    
        case AddAssignOp:
            newIntValue = integerLeft->value() + integerRight->value();      
            break;      
        case SubAssignOp:
            newIntValue = integerLeft->value() - integerRight->value();      
            break;                
        case MulAssignOp:      
            newIntValue = integerLeft->value() * integerRight->value();      
            break;          
        case DivAssignOp:       
            newIntValue = integerLeft->value() / integerRight->value();      
            break;         
        case ModAssignOp:
            newIntValue = integerLeft->value() % integerRight->value();      
            break;
        case ConcatAssignOp:
        default:
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Operacao de atribuicao utilizada invalida para inteiros";
            throw error.str();              
    }

    IntegerValue* intValue = new IntegerValue(newIntValue);

    switch(m_left->type()) {        
        case Expr::VarVarExpr:
            varVarExpr = (VarVarExpr*) m_left;
            varVarExpr->setExpr(intValue);
            return;
        case Expr::Variable:
            variable = (Variable*) m_left;
            variable->setExpr(intValue);
            return;
        case Expr::AccessExpr:
            accessExpr = (AccessExpr*) m_left;
            accessExpr->setExpr(intValue);            
            return;
        default:
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Operacoes de atribuicao sao invalidas para expressoes imutaveis";
            throw error.str();
    }

}