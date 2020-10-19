#include <iostream>
#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"
#include "interpreter/command/BlocksCommand.h"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [MiniPHP program]" << std::endl;
        return 0;
    }

    try {
        Lexeme lex;        
        LexicalAnalysis l(argv[1]);
        SyntaticAnalysis syn(l);
        
        BlocksCommand* code = syn.start(); 

        try {
            code -> execute ();    
        }
        catch (const std::string& error) {
            throw std::string("Operacao invalida: " + error);
        }

    } catch (const std::string& error) {
        std::cerr << error << std::endl;
    }

    return 0;
}
