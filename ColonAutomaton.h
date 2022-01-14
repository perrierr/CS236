#pragma once
//#ifndef COLONAUTOMATON_H
//#define COLONAUTOMATON_H

#include "Automaton.h"

class ColonAutomaton : public Automaton
{
public:
    TokenType type;

public:
    ColonAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    void S0(const std::string& input);

    ColonAutomaton(TokenType type) {
        this->type = type;
    }
};

//#endif // COLONAUTOMATON_H

