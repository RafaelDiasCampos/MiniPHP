#ifndef FOREACH_COMMAND_H
#define FOREACH_COMMAND_H

#include "Command.h"
#include "../expr/Expr.h"
#include "../expr/Variable.h"
#include "../expr/ExprUtils.h"
#include "../value/StringValue.h"

class ForeachCommand : public Command {
    public:
        ForeachCommand(int line, Expr* expr, Command* cmds, Variable* key, Variable* value = 0);
        virtual ~ForeachCommand();

        void execute();

    private:
        Expr* m_expr;
        Command* m_cmds;
        Variable* m_key, *m_value;
};

#endif