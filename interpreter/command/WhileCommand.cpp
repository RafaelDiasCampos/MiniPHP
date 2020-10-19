#include "WhileCommand.h"


WhileCommand::WhileCommand(int line, BoolExpr* cond, Command* cmds) : Command(line), m_cond(cond), m_cmds(cmds) {

}

WhileCommand::~WhileCommand() {

}

void WhileCommand::execute() {
    while (ExprUtils::getExpr(m_cond)) {
        m_cmds->execute();
    }
}