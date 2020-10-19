#ifndef TYPE_H
#define TYPE_H

class Type {
    public:
        enum ValueType {
            IntegerType,
            StringType,
            ArrayType
        };

        Type(Type::ValueType type) : m_type(type) {}
        virtual ~Type() {}

        Type::ValueType type() const { return m_type; }

    private:
        Type::ValueType m_type;
};

#endif