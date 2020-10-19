#include "ReadExpr.h"

ReadExpr::ReadExpr(int line, Expr* msg) : Expr(line, Expr::ReadExpr), m_msg(msg) {

}

ReadExpr::~ReadExpr() {

}

Type* ReadExpr::expr() {
    EchoCommand* echo = new EchoCommand(m_line, m_msg);

    echo->execute();  

    std::string readValue;
    int intValue;

    std::cin >> readValue;

    try { //Tries converting to an int
        intValue = std::stoi(readValue);
        return new IntegerValue(intValue);
    }
    catch (...) {
        return new StringValue(readValue);
    }    
    
}