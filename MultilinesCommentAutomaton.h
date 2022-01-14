#pragma once

#include "Automaton.h"

class MultilinesCommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);


public:
    MultilinesCommentAutomaton() : Automaton(TokenType::COMMENT) {

    }  // Call the base constructor
        void S0(const std::string& input);

};



