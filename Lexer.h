#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

class Lexer
{
private:


    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    int maxRead = 0;
    int inputRead = 0;
    int index = 0;
    int lineNumber = 0;
    Automaton *maxAutomaton;

    void CreateAutomata();
    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();
    void Run(std::string& input);
    std::vector<Token*> GetTokens();

    // TODO: add other public methods here

};

#endif // LEXER_H
