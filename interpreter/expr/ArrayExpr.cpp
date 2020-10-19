#include <sstream>
#include <iomanip>
#include "ArrayExpr.h"

ArrayExpr::ArrayExpr(int line) : Expr(line, Expr::ArrayExpr) {

}

ArrayExpr::~ArrayExpr() {

}

Type* ArrayExpr::expr() {
    std::stringstream error;

    std::map<std::string, Type*> array;

    std::string key;
    Type *keyType;
    Type* value;

    for (auto i : m_array) {
        keyType = ExprUtils::getExpr(i.first);

        switch (keyType->type()) {
            case Type::IntegerType:
                key = std::to_string (( (IntegerValue*) keyType)->value());
                break;
            case Type::StringType:
                key = ( (StringValue*) keyType)->value();
                break;
            case Type::ArrayType:
                error << std::setw(2) << std::setfill('0') << m_line << ": ";
                error << "O indice nao pode ser um array";
                throw error.str();
        }

        value = ExprUtils::getExpr(i.second);

        array.insert( std::pair<std::string, Type*>(key, value) );
    }

    return new ArrayValue(array);
}

void ArrayExpr::insert(Expr* key, Expr* value) {
    m_array.insert( std::pair<Expr*, Expr*> (key, value) );
}