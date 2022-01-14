#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "Token.h"

class Automaton
{
public:
    int inputRead;
    int newLines;
    unsigned int index;
    TokenType type;

public:
    // Default constructor -- since we have a constructor that takes a parameter,
    //   the compiler will autogenerate a default constructor if not explicit.
    Automaton() : Automaton(TokenType::UNDEFINED) {
    }

    virtual ~Automaton() {

    }

    Automaton(TokenType type) {
        this->type = type;
    }

    // Start the automaton and return the number of characters read
    //   read == 0 indicates the input was rejected
    //   read  > 0 indicates the input was accepted
    int Start(const std::string& input) {
        inputRead = 0;
        index = 0;
        newLines = 0;
        S0(input);
        return inputRead;
    }


    virtual void S0(const std::string& input) {

    }

    void Serr() {
        inputRead = 0;
    }

    Token* CreateToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber);
    }

    int NewLinesRead() {

        return newLines;
    }
};

#endif // AUTOMATON_H