#include "FactsAutomaton.h"

void FactsAutomaton::S0(const std::string& input) {

    index = 0;

    if (input[index] == 'F') {
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

void FactsAutomaton::S1(const std::string& input) {
    if (input[index] == 'a') {
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

void FactsAutomaton::S2(const std::string& input) {
    if (input[index] == 'c') {
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

void FactsAutomaton::S3(const std::string& input) {
    if (input[index] == 't') {
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

void FactsAutomaton::S4(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}

