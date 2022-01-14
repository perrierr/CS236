#include "RulesAutomaton.h"

void RulesAutomaton::S0(const std::string& input) {
    index = 0;
    if (input[index] == 'R') {
        inputRead++;
        index++;
        if (input[index] == ' ' || input[index] == '\n' || input[index] == '\t') {
            inputRead = 0;
            Serr();
        }
        S1(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S1(const std::string& input) {
    if (input[index] == 'u') {
        inputRead++;
        index++;
        if (input[index] == ' ' || input[index] == '\n' || input[index] == '\t') {
            inputRead = 0;
            Serr();
        }
        S2(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S2(const std::string& input) {
    if (input[index] == 'l') {
        inputRead++;
        index++;
        if (input[index] == ' ' || input[index] == '\n' || input[index] == '\t') {
            inputRead = 0;
            Serr();
        }
        S3(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S3(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
        index++;
        if (input[index] == ' ' || input[index] == '\n' || input[index] == '\t') {
            inputRead = 0;
            Serr();
        }
        S4(input);
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S4(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    } else {
        Serr();
    }
}

