#pragma once

#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    TokenType type;

public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}  // Call the base constructor

    void S0(const std::string& input);

    CommaAutomaton(TokenType type) {
        this->type = type;
    }
};



