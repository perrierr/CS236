#include "IDAutomaton.h"


void IDAutomaton::S0(const std::string& input) {
    index = 0;
    newLines = 0;
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IDAutomaton::S1(const std::string& input) {

        while (isalpha(input[index]) || isdigit(input[index])) {
            inputRead++;
            index++;
        }

    }


