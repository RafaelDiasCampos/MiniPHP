#ifndef ASSIGN_COMMAND_H
#define ASSIGN_COMMAND_H

#include "Command.h"
#include "../expr/Expr.h"
#include "../expr/Variable.h"
#include "../expr/ExprUtils.h"

enum AssignOp {
    NoAssignOp = 1,
    StdAssignOp,
    AddAssignOp,
    SubAssignOp,
    ConcatAssignOp,
    MulAssignOp,
    DivAssignOp,
    ModAssignOp
};

class AssignCommand : public Command {
    public:
        AssignCommand(int line, Expr* left, AssignOp op, Expr* right = 0);
        virtual ~AssignCommand();

        void execute();

    private:
        Expr* m_left;
        AssignOp m_op;
        Expr *m_right;
};

#endif