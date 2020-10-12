#include <iostream>
#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"

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
        

        // while ((lex = l.nextToken()).type > 0) {
        //     std::cout << lex.str() << std::endl;            
        // }
        // std::cout << lex.str() << std::endl;

        syn.start(); 

    } catch (const std::string& error) {
        std::cerr << error << std::endl;
    }

    return 0;
}
