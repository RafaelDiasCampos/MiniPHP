#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <map>
#include "SetExpr.h"
#include "../util/Memory.h"

class Variable : public SetExpr {
    public:
        Variable(std::string name);
        virtual ~Variable();

        Type* expr();
        static Variable* instance(std::string name);
        std::string name();
        void setExpr(Type* value);
        
    private: 
        std::string m_name;
};

#endif