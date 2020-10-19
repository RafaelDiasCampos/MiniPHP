#include "IfCommand.h"

IfCommand::IfCommand(int line, BoolExpr* cond, Command* thenCmds) : Command(line), m_cond(cond), m_thenCmds(thenCmds) {

}

IfCommand::~IfCommand() {

}

void IfCommand::execute() {
    if (ExprUtils::getExpr(m_cond)) {
        m_thenCmds->execute();
    }
    else if (m_elseCmds) {
        if (m_elseCmds) m_elseCmds->execute();
    }
}

void IfCommand::addElseCommands(Command* elseCmds) {
    m_elseCmds = elseCmds;
}