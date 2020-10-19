#ifndef COMMAND_H
#define COMMAND_H

class Command {
    public: 
        Command (int line): m_line(line) {}
        virtual ~Command() {}

        int line() const {return m_line; }
        virtual void execute() {}

    protected:
        int m_line;

};

#endif