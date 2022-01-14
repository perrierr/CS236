#pragma once

#include "Automaton.h"

class Q_MarkAutomaton : public Automaton
{
public:
    TokenType type;

public:
    Q_MarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);

    Q_MarkAutomaton(TokenType type) {
        this->type = type;
    }
};


