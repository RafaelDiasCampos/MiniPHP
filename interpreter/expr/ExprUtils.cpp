#include "ExprUtils.h"

Type* ExprUtils::getExpr(Expr* expr) {
    ArrayExpr* arrayExpr;
    BinaryExpr* binaryExpr;
    ConstExpr* constExpr;
    ReadExpr* readExpr;
    VarVarExpr* varVarExpr;
    Variable* variable;
    AccessExpr* accessExpr;
    UnaryExpr* unaryExpr;

    switch(expr->type()) {        
        case Expr::ArrayExpr:
            arrayExpr = (ArrayExpr*) expr;
            return arrayExpr->expr();    
        case Expr::BinaryExpr:
            binaryExpr = (BinaryExpr*) expr;
            return binaryExpr->expr();    
        case Expr::ConstExpr:
            constExpr = (ConstExpr*) expr;
            return constExpr->expr();    
        case Expr::ReadExpr:
            readExpr = (ReadExpr*) expr;
            return readExpr->expr();    
        case Expr::VarVarExpr:
            varVarExpr = (VarVarExpr*) expr;
            return varVarExpr->expr();
        case Expr::Variable:
            variable = (Variable*) expr;
            return variable->expr(); 
        case Expr::AccessExpr:
            accessExpr = (AccessExpr*) expr;
            return accessExpr->expr();    
        case Expr::UnaryExpr:
        default:
            unaryExpr = (UnaryExpr*) expr;
            return unaryExpr->expr();    
    }

}

bool ExprUtils::getExpr(BoolExpr* expr) {
    SingleBoolExpr* singleBoolExpr;
    NotBoolExpr* notBoolExpr;
    CompositeBoolExpr* compositeBoolExpr;

    switch(expr->type()) {
        case BoolExpr::SingleBoolExpr:
            singleBoolExpr = (SingleBoolExpr*) expr;
            return singleBoolExpr->expr();
        case BoolExpr::NotBoolExpr:
            notBoolExpr = (NotBoolExpr*) expr;
            return notBoolExpr->expr();
        case BoolExpr::CompositeBoolExpr:
        default:
            compositeBoolExpr = (CompositeBoolExpr*) expr;
            return compositeBoolExpr->expr();
    }   
}