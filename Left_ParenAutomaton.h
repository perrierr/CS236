#pragma once

#include "Automaton.h"

class Left_ParenAutomaton : public Automaton
{
public:
    TokenType type;

public:
    Left_ParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);

    Left_ParenAutomaton(TokenType type) {
        this->type = type;
    }
};


