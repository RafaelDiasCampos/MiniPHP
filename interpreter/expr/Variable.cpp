#include "Variable.h"
#include "../value/ArrayValue.h"

Variable::Variable(std::string name) : SetExpr(-1, Expr::Variable), m_name(name) {
}

Variable::~Variable() {

}

Type* Variable::expr() {
    return Memory::read(m_name);
}

Variable* Variable::instance(std::string name) {
    return new Variable(name);
}

std::string Variable::name() {
    return m_name;
}

void Variable::setExpr(Type* value) {
    Memory::write(m_name, value);
}