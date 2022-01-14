#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "LineCommentAutomaton.h"
#include "IDAutomaton.h"
#include "MultilinesCommentAutomaton.h"
#include "StringAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include <cctype>

using namespace std;


Lexer::Lexer() {
    CreateAutomata();
}

//============================================================================================

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
    for (unsigned int i = 0; i < automata.size(); i++) {
        delete automata.at(i);
    }

    for (unsigned int i = 0; i < tokens.size(); i++) {
        delete tokens.at(i);
    }

}

//============================================================================================


void Lexer::CreateAutomata() {

    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new LineCommentAutomaton());
    automata.push_back(new MultilinesCommentAutomaton());


    //cout << automata.size() << endl;
    // TODO: Add the other needed automata here
}


//============================================================================================





//============================================================================================

void Lexer::Run(std::string &input) {    // TODO: convert this pseudo-code with the algorithm into actual C++ code

    lineNumber = 1;
    while (input.size() > 0) {
        maxRead = 0;
        maxAutomaton = automata[0];


        //cout << "Phase 1 done" << endl;

        //TODO HANDLE WHITE SPACE
        while (isspace(input[0])) {
            //cout << "Phase 1a done" << endl;

            if (input[0] == '\n') {
                lineNumber++;
            }
            input.erase(0, 1);
        }

        //cout << "Phase 2 done" << endl;


        for (unsigned int i = 0; i < automata.size(); ++i) {
            //cout << "inside automata loop" << endl;
            inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = automata[i];
            }
        }

        string newString;
        if (maxRead > 0) {
            newString = input.substr(0, maxRead);
            //           for (unsigned int i = 0; i < newString.size(); i++) {
            //               if (newString[i] == '\t') {
            //                   newString.erase(i, 1);
            //                   newString.insert(i, " ");
            //               }
            //          }
            // cout << "newString" << newString << endl;

            if (maxAutomaton->type != TokenType::COMMENT) {
                Token *newToken = maxAutomaton->CreateToken(newString, lineNumber);
                tokens.push_back(newToken);
            }
            lineNumber += maxAutomaton->NewLinesRead();

        } else {
            maxRead = 1;
            if (input == "") {
                break;
            } else {
                Token *newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNumber);
                tokens.push_back(newToken);
            }
        }
        input.erase(0, maxRead);
    }

    Token *newToken = new Token(TokenType::EOFa, "", lineNumber);
    tokens.push_back(newToken);

/*   for (unsigned int i = 0; i < tokens.size(); i++) {
        //if (tokens.at(i)->GetType() == "STRING" || tokens.at(i)->GetType() == "ID") {
            cout << tokens.at(i)->toString() << endl;
        //}
    }*/


/*     cout << "Total Tokens = " << tokens.size();
    myToken = ss.str();
    cout << "Stringstream : " << myToken << endl;
    cout << maxRead << "MaxRead " << endl;*/



//}

//=======================================================================================


}

std::vector<Token *> Lexer::GetTokens() {

    return tokens;

}
