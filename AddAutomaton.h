#ifndef LAB_1_ADDAUTOMATON_H
#define LAB_1_ADDAUTOMATON_H


#include "Automaton.h"


class AddAutomaton : public Automaton
{
public:
    TokenType type;

public:
    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

    void S0(const std::string& input);

    AddAutomaton(TokenType type) {
        this->type = type;
    }
};

#endif //LAB_1_ADDAUTOMATON_H
