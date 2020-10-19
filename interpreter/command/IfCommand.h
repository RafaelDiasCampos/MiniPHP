#ifndef IF_COMMAND_H
#define IF_COMMAND_H

#include "Command.h"
#include "../expr/BoolExpr.h"
#include "../expr/ExprUtils.h"

class IfCommand : public Command {
    public:
        IfCommand(int line, BoolExpr* cond, Command* thenCmds);
        virtual ~IfCommand();

        void execute();
        void addElseCommands(Command* elseCmds);

    private:
        BoolExpr* m_cond;
        Command* m_thenCmds, *m_elseCmds;
};

#endif