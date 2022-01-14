#include "StringAutomaton.h"
#include <sstream>
#include <iostream>

void StringAutomaton::S0(const std::string &input) {

    //char myChar = input[index];
    if (input[index] == '\'') { // start of string
        index++;
        inputRead++;
        S1(input);
    }

}


void StringAutomaton::S1(const std::string &input) {

    // we are in a string.... find the end ' (if it exists)

        if(input.size() == index) {
            type = UNDEFINED;
        }

        if (input[index] == '\'') {
            inputRead++;
            index++;
            S2(input);
        } else {
            if (input[index] == '\n') {
             newLines++;
            }
            inputRead++;
            index++;
            S1(input);
        }


}

void StringAutomaton::S2(const std::string &input) {

            if (input[index] == '\'') {
                index++;
                inputRead++;
                S1(input);
            }


}
