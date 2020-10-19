#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <map>
#include "../value/IntegerValue.h"
#include "../value/Type.h"

class Memory {
    public:
        static Type* read(const std::string& name);
        static void write(const std::string& name, Type* var);
    
    private:
        static std::map<std::string, Type*> m_memory;
};

#endif