#pragma once

#include "Automaton.h"

class LineCommentAutomaton: public Automaton
{
private:
    void S1(const std::string& input);


public:
    LineCommentAutomaton() : Automaton(TokenType::COMMENT) {

    }  // Call the base constructor
        void S0(const std::string& input);

};



