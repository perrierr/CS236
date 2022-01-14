#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Database.h"

using namespace std;

int main(int argc, char **argv) {


    string fileName = argv[1];
    ifstream inFS;

    inFS.open(fileName);

    if (inFS.fail()) {
        //cout << "File does not exist" << endl;
    }

    string line;
    stringstream ss;
    while (getline(inFS, line)) {
        ss << line << '\n';
    }

    line = ss.str();
    // cout << line << endl;

    Lexer *lexer = new Lexer();
    lexer->Run(line);


/*    //testing
    vector <Token*> myTokens = lexer->GetTokens();
    for (unsigned int i = 0; i < myTokens.size(); i++) {
        cout << myTokens.at(i)->GetType() << endl;
    }*/

    Parser* parser = new Parser();

    try {
        parser->ParseInput(lexer->GetTokens());
    } catch(string exception) {
        cout << exception << endl;
    }


    Database* database = new Database();

    database->CreateMapKeyHeader(parser->GetSchemesList());
    database->AddTuples(parser->GetFactsList());
    database->OptimizeRules(parser->GetRulesList());
    //database->CreateRules(parser->GetRulesList());
    database->CreateQueries(parser->GetQueriesList());



    //database->CreateMapKeyHeader(datalogProgram->GetVectorSchemes(), datalogProgram->GetVectorFacts(), datalogProgram->GetVectorQueries());

//    StringAutomaton * st = new StringAutomaton();
//    st->S0("'Hi'");
//    st->S0("'' 'Hi'");
//    st->S0("''");
//    st->S0("'''"); // 0
//    st->S0("'\n''\n'''\n'"); // 8
//    st->S0("'\n''\n''''\n'"); // 11
//
//    cout << "Input read: " << st->inputRead;




    return 0;
}