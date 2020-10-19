#ifndef INTERPRETER_DEPENDENCIES_H
#define INTERPRETER_DEPENDENCIES_H

#include "../interpreter/util/Memory.h"

#include "../interpreter/value/IntegerValue.h"
#include "../interpreter/value/StringValue.h"
#include "../interpreter/value/ArrayValue.h"

#include "../interpreter/expr/ConstExpr.h"
#include "../interpreter/expr/ReadExpr.h"
#include "../interpreter/expr/ArrayExpr.h"
#include "../interpreter/expr/VarVarExpr.h"
#include "../interpreter/expr/Variable.h"
#include "../interpreter/expr/AccessExpr.h"
#include "../interpreter/expr/UnaryExpr.h"
#include "../interpreter/expr/BinaryExpr.h"
#include "../interpreter/expr/SingleBoolExpr.h"
#include "../interpreter/expr/NotBoolExpr.h"
#include "../interpreter/expr/CompositeBoolExpr.h"
#include "../interpreter/expr/ExprUtils.h"

#include "../interpreter/command/BlocksCommand.h"
#include "../interpreter/command/EchoCommand.h"
#include "../interpreter/command/WhileCommand.h"
#include "../interpreter/command/AssignCommand.h"
#include "../interpreter/command/IfCommand.h"
#include "../interpreter/command/ForeachCommand.h"

#endif
