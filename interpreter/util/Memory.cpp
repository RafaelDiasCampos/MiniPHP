#include "Memory.h"
#include <iostream>

std::map<std::string, Type*> Memory::m_memory;

Type* Memory::read (const std::string& name) {
    auto key = m_memory.find(name);

    if (key != m_memory.end()) {
        return key->second;
    }

    Type* newVar = new IntegerValue(0);

    m_memory.insert(std::pair<std::string, Type*> (name, newVar));

    return newVar;
}

void Memory::write (const std::string& name, Type* var) {
    m_memory[name] = var;
}