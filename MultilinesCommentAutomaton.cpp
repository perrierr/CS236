#include "MultilinesCommentAutomaton.h"

void MultilinesCommentAutomaton::S0(const std::string& input) {


    index = 0;
    if (input[index] == '#') {
        index++;
        inputRead++;
        S1(input);
    }

    else {
        Serr();
    }
}


void MultilinesCommentAutomaton::S1(const std::string& input) {

    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);

    } else {
        Serr();
    }
}

void MultilinesCommentAutomaton::S2(const std::string& input) {

    for (unsigned int i = index; i < input.size(); i++) {
        if (input[index] == '|') {
            inputRead++;
            index++;
            if (input[index] == '#') {
                inputRead++;
                index++;
                return;
            }
        } else if (input[index] == '\n') {
            inputRead++;
            index++;
            newLines++;
        } else {
            inputRead++;
            index++;
    }
}

    type = UNDEFINED;
}


