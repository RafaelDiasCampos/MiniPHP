#include "IntegerValue.h"

IntegerValue::IntegerValue(int value)
  : Value(Type::IntegerType), m_value(value) {
}

IntegerValue::~IntegerValue() {
}

int IntegerValue::value() const {
    return m_value;
}
