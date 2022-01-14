#pragma once

#include "Automaton.h"

class PeriodAutomaton : public Automaton
{
public:
    TokenType type;

public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input);

    PeriodAutomaton(TokenType type) {
        this->type = type;
    }
};


