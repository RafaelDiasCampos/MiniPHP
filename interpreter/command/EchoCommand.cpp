#include <iostream>
#include <sstream>
#include <iomanip>
#include "EchoCommand.h"


EchoCommand::EchoCommand(int line, Expr* expr): Command(line), m_expr(expr) {


}

EchoCommand::~EchoCommand() {

}


void EchoCommand::execute() {
    std::stringstream error;

    Type* v = ExprUtils::getExpr(m_expr);

    switch (v->type()) {
        case Type::StringType: {
            StringValue* stringValue = (StringValue*) v;
            std::cout << stringValue->value() << std::flush;
            return;
        }
            
        case Type::IntegerType: {
            IntegerValue* integerValue = (IntegerValue*) v;
            std::cout << integerValue->value() << std::flush;
            return;
        }            
        case Type::ArrayType: {
            error << std::setw(2) << std::setfill('0') << m_line << ": ";
            error << "Comando echo invalido para arrays";
            throw error.str();
        }                        
    }
}


