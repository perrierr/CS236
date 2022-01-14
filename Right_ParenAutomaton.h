#pragma once

#include "Automaton.h"

class Right_ParenAutomaton : public Automaton
{
public:
    TokenType type;

public:
    Right_ParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);

    Right_ParenAutomaton(TokenType type) {
        this->type = type;
    }
};


