#ifndef ECHO_COMMAND_H
#define ECHO_COMMAND_H

#include "../value/IntegerValue.h"
#include "../value/StringValue.h"
#include "Command.h"
#include "../expr/Expr.h"
#include "../expr/ExprUtils.h"

class EchoCommand : public Command {
    public:
        EchoCommand(int line, Expr* expr);
        virtual ~EchoCommand();

        void execute();

    private:
        Expr* m_expr;

};

#endif