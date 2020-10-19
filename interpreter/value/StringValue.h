#ifndef STRING_VALUE_H
#define STRING_VALUE_H

#include "Value.h"

#include <string>

class StringValue : public Value<std::string> {
    public:
        StringValue(std::string value);
        virtual ~StringValue();

        std::string value() const;

    private:
        std::string m_value;
};

#endif
