#include "SchemesAutomaton.h"

void SchemesAutomaton::S0(const std::string& input) {
    index = 0;
    newLines = 0;
    if (input[index] == 'S') {
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

void SchemesAutomaton::S1(const std::string& input) {
    if (input[index] == 'c') {
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

void SchemesAutomaton::S2(const std::string& input) {
    if (input[index] == 'h' || input[index] == 'H') {
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

void SchemesAutomaton::S3(const std::string& input) {
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

void SchemesAutomaton::S4(const std::string& input) {
    if (input[index] == 'm') {
        inputRead++;
        index++;
        if (input[index] == ' ' || input[index] == '\n' || input[index] == '\t') {
            inputRead = 0;
            Serr();
        }
        S5(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S5(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
        index++;
        if (input[index] == ' ' || input[index] == '\n' || input[index] == '\t') {
            inputRead = 0;
            Serr();
        }
        S6(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S6(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}

