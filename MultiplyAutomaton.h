#ifndef LAB_1_MULTIPLYAUTOMATON_H
#define LAB_1_MULTIPLYAUTOMATON_H

#include "Automaton.h"


class MultiplyAutomaton : public Automaton
{
public:
    TokenType type;

public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input);

    MultiplyAutomaton(TokenType type) {
        this->type = type;
    }
};


#endif //LAB_1_MULTIPLYAUTOMATON_H
