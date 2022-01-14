#include "LineCommentAutomaton.h"

void LineCommentAutomaton::S0(const std::string& input) {

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

void LineCommentAutomaton::S1(const std::string& input) {

    char myChar;

    while (true) {
        myChar = input.at(index);

        if(input[1] == '|') {
            break;
        }

        if (myChar == '\n') {
            break;
        }

        else if (myChar == EOF) {
            break;
        }
        else {
        index++;
        inputRead++;

        }

    }

}


