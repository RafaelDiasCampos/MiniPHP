#include "ArrayValue.h"

ArrayValue::ArrayValue(const std::map<std::string,Type*>& value)
	: Value(Type::ArrayType), m_value(value) {
}

ArrayValue::~ArrayValue() {
}

std::map<std::string,Type*> ArrayValue::value() const {
    return m_value;
}

void ArrayValue::setValue(std::map<std::string,Type*> value) {
    m_value = value;
}
