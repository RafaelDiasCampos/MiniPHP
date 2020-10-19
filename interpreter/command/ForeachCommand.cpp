#include <sstream>
#include <iomanip>
#include "ForeachCommand.h"

ForeachCommand::ForeachCommand(int line, Expr* expr, Command* cmds, Variable* key, Variable* value) : Command(line), m_expr(expr), m_cmds(cmds), m_key(key), m_value(value) {

}

ForeachCommand::~ForeachCommand() {

}

void ForeachCommand::execute() {
    std::stringstream error;

    Type* arrayType = ExprUtils::getExpr(m_expr);

    if (arrayType->type() != Type::ArrayType) {
        error << std::setw(2) << std::setfill('0') << m_line << ": ";
        error << "Comando foreach deve receber um array como expressao";
        throw error.str();
    }

    auto array = ( (ArrayValue*) arrayType)->value();

    for (auto element : array) {
        m_key->setExpr(new StringValue(element.first));
        if (m_value) m_value->setExpr(element.second);

        m_cmds->execute();
    }
    
}