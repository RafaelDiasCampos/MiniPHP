#ifndef ARRAY_VALUE_H
#define ARRAY_VALUE_H

#include "Value.h"

#include <map>
#include <string>

class Type;

class ArrayValue : public Value<std::map<std::string,Type*> > {
    public:
        ArrayValue(const std::map<std::string,Type*>& value);
        virtual ~ArrayValue();

        std::map<std::string,Type*> value() const;
        void setValue(std::map<std::string,Type*> value);

    private:
        std::map<std::string,Type*> m_value;
};

#endif
