#pragma once

#include "Token.h"
#include <vector>
#include "Rule.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include <set>

class Parser {

private:
    int currentTokenIndex = 0;
    int index = 0;
    vector<Token *> tokenStorage;
    vector<Predicate*> schemesList;
    vector<Predicate*> factsList;
    vector<Predicate*> queriesList;
    vector<Rule*> ruleLists;
    set <string> domainLists;

public:
    Parser() {}
    ~Parser() {

    }

    void ParseInput(vector<Token *> input) {
        tokenStorage = input;
/*        for (int i = 0; i < tokenStorage.size(); i++) {
            cout << tokenStorage.at(i)->toString() << endl;
        }*/
        ParseDatalogProgram();
    }

    /* void CreateDatalogProgramSchemes(vector<Predicate*> myPredicate) {

         DatalogProgram *newDatalogProgram = new DatalogProgram();

         newDatalogProgram->SetSchemesPredicate( myPredicate);
     }

     void CreateDatalogProgramFacts(vector<Predicate*> myPredicate) {

         DatalogProgram *newDatalogProgram = new DatalogProgram();

         newDatalogProgram->SetFactsPredicate( myPredicate);
     }

     void CreateDatalogProgramQueries(vector<Predicate*> myPredicate) {

         DatalogProgram *newDatalogProgram = new DatalogProgram();

         newDatalogProgram->SetQueriesPredicate(myPredicate);
     }*/

    void Match(int index, string type) {
        string value = tokenStorage.at(index)->GetType();
        if (tokenStorage.at(index)->GetType() == type) {
            currentTokenIndex++;
        } else {
            string TokenException;
            ostringstream ss;
            ss << "Failure!\n"
               << tokenStorage.at(currentTokenIndex)->toString();
            TokenException = ss.str();
            throw TokenException;
        }
    }

    void ParseDatalogProgram() {
        //datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList COLON query queryList EOF
        Match(currentTokenIndex, "SCHEMES");
        Match(currentTokenIndex, "COLON");
        ParseScheme();
        ParseSchemeList();

        Match(currentTokenIndex, "FACTS");
        Match(currentTokenIndex, "COLON");
        ParseFactList();

        Match(currentTokenIndex, "RULES");
        Match(currentTokenIndex, "COLON");
        ParseRuleList();

        Match(currentTokenIndex, "QUERIES");
        Match(currentTokenIndex, "COLON");
        ParseQuery();
        ParseQueryList();

        Match(currentTokenIndex, "EOF");

/*        //COMMENTED THIS BLOCK FOR PROJECT 3
        cout << "Success!\n";


        cout <<"Schemes(" << schemesList.size() << "):" << endl;
        for(unsigned int i = 0; i < schemesList.size(); i++) {
            cout <<"  ";
            schemesList.at(i)->PrintSchemes();
            cout << endl;
        }

        cout <<"Facts(" << factsList.size() << "):" << endl;
        for(unsigned int i = 0; i < factsList.size(); i++) {
            cout <<"  ";
            factsList.at(i)->PrintFacts();
            cout << endl;
        }

        cout << "Rules(" << ruleLists.size() << "):" << endl;
        for(unsigned int i = 0; i < ruleLists.size(); i++) {
            cout <<"  ";
            ruleLists.at(i)->Select();
            cout << endl;
        }

        cout <<"Queries(" << queriesList.size() << "):" << endl;
        for(unsigned int i = 0; i < queriesList.size(); i++) {
            cout <<"  ";
            queriesList.at(i)->PrintQueries();
            cout << endl;
        }

        cout << "Domain(" << domainLists.size() << "):" << endl;
        for (auto itr = domainLists.begin(); itr != domainLists.end(); itr++) {
            cout << "  " << *itr << endl;
        }*/

/*        CreateDatalogProgramSchemes(schemesList);
        CreateDatalogProgramFacts(factsList);
        CreateDatalogProgramQueries(queriesList);*/
    }

    void ParseScheme() {

        //SetName for newSchemePredicate
        Predicate *predicate = new Predicate();
        predicate->SetName(tokenStorage.at(currentTokenIndex)->GetDescription());
        schemesList.push_back(predicate);
        //cout << "GetName of newPredicate " << newPredicate.GetName() << endl;
        Match(currentTokenIndex, "ID");
        Match(currentTokenIndex, "LEFT_PAREN");

        Parameter *newParameter = new Parameter();
        newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
        predicate->Add(newParameter);
        Match(currentTokenIndex, "ID");
        ParseIDList(predicate);

        Match(currentTokenIndex, "RIGHT_PAREN");
    }

    void ParseSchemeList() {
        if (tokenStorage.at(currentTokenIndex)->GetType() != "FACTS") {
            ParseScheme();
            ParseSchemeList();
        }
    }

    void ParseFact() {
        //ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
        Predicate *predicate = new Predicate();
        predicate->SetName(tokenStorage.at(currentTokenIndex)->GetDescription());
        factsList.push_back(predicate);
        Match(currentTokenIndex, "ID");
        Match(currentTokenIndex, "LEFT_PAREN");

        Parameter *newParameter = new Parameter();
        newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
        predicate->Add(newParameter);
        domainLists.insert(tokenStorage.at(currentTokenIndex)->GetDescription());
        Match(currentTokenIndex, "STRING");
        ParseStringList(predicate);
        Match(currentTokenIndex, "RIGHT_PAREN");
        Match(currentTokenIndex, "PERIOD");
    }

    void ParseFactList() {
        if (tokenStorage.at(currentTokenIndex)->GetType() != "RULES") {
            ParseFact();
            ParseFactList();
        }
    }

    void ParseIDList(Rule *rule, Predicate *predicate) {
        //COMMA ID idList | lambda
        if (tokenStorage.at(currentTokenIndex)->GetType() != "RIGHT_PAREN") {
            //Dont need to store comma
            Match(currentTokenIndex, "COMMA");

            Parameter *newParameter = new Parameter();
            newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
            predicate->Add(newParameter);
            Match(currentTokenIndex, "ID");
            ParseIDList(rule, predicate);
        }
    }

    void ParseIDList(Predicate *predicate) {
        //COMMA ID idList | lambda

        if (tokenStorage.at(currentTokenIndex)->GetType() != "RIGHT_PAREN") {
            //Dont need to store comma
            Match(currentTokenIndex, "COMMA");

            Parameter *newParameter = new Parameter();
            newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
            predicate->Add(newParameter);
            Match(currentTokenIndex, "ID");
            ParseIDList(predicate);
        }
    }

    void ParseStringList(Predicate *predicate) {
        //COMMA STRING stringList | lambda

        if (tokenStorage.at(currentTokenIndex)->GetType() != "RIGHT_PAREN") {

            Match(currentTokenIndex, "COMMA");

            //Create Domain
            Parameter *newParameter = new Parameter();
            newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
            predicate->Add(newParameter);
            domainLists.insert(tokenStorage.at(currentTokenIndex)->GetDescription());
            Match(currentTokenIndex, "STRING");

            ParseStringList(predicate);
        }
    }

    void ParseRuleList() {
        if (tokenStorage.at(currentTokenIndex)->GetType() != "QUERIES") {
            ParseRule();
            ParseRuleList();
        }
    }

    void ParseRule() {
        //headPredicate COLON_DASH predicate predicateList PERIOD

        Rule *rule = new Rule();
        ruleLists.push_back(rule);
        ParseHeadPredicate(rule);
        Match(currentTokenIndex, "COLON_DASH");

        ParsePredicate(rule);
        ParsePredicateList(rule);
        Match(currentTokenIndex, "PERIOD");
    }

    void ParseHeadPredicate(Rule *rule) {

        Predicate *predicate = new Predicate();
        predicate->SetName(tokenStorage.at(currentTokenIndex)->GetDescription());
        rule->SetHeadPredicate(predicate);
        Match(currentTokenIndex, "ID");
        Match(currentTokenIndex, "LEFT_PAREN");

        Parameter *newParameter = new Parameter();
        newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
        predicate->Add(newParameter);
        Match(currentTokenIndex, "ID");

        ParseIDList(rule, predicate);
        Match(currentTokenIndex, "RIGHT_PAREN");
    }

    void ParseParameter(Rule *rule, Predicate *predicate) {
        //Moved to Parameter Class
        if (tokenStorage.at(currentTokenIndex)->GetType() == "STRING") {
            Parameter *newParameter = new Parameter();
            newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
            predicate->Add(newParameter);
            Match(currentTokenIndex, "STRING");
        }
        if (tokenStorage.at(currentTokenIndex)->GetType() == "ID") {
            Parameter *newParameter = new Parameter();
            newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
            predicate->Add(newParameter);
            Match(currentTokenIndex, "ID");
        }
    }

    void ParseParameter(Predicate *predicate) {
        //Moved to Parameter Class
        if (tokenStorage.at(currentTokenIndex)->GetType() == "STRING") {
            Parameter *newParameter = new Parameter();
            newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
            predicate->Add(newParameter);
            Match(currentTokenIndex, "STRING");
        }
        if (tokenStorage.at(currentTokenIndex)->GetType() == "ID") {
            Parameter *newParameter = new Parameter();
            newParameter->Set(tokenStorage.at(currentTokenIndex)->GetDescription());
            predicate->Add(newParameter);
            Match(currentTokenIndex, "ID");
        }
    }

    void ParseParameterList(Rule *rule, Predicate *predicate) {
        if (tokenStorage.at(currentTokenIndex)->GetType() != "RIGHT_PAREN") {
            Match(currentTokenIndex, "COMMA");
            ParseParameter(rule, predicate);
            ParseParameterList(rule, predicate);
        }
    }

    void ParseParameterList(Predicate *predicate) {
        if (tokenStorage.at(currentTokenIndex)->GetType() != "RIGHT_PAREN") {
            Match(currentTokenIndex, "COMMA");
            ParseParameter(predicate);
            ParseParameterList(predicate);
        }
    }

    void ParsePredicateList(Rule *rule) {
        if (tokenStorage.at(currentTokenIndex)->GetType() != "PERIOD") {
            Match(currentTokenIndex, "COMMA");
            ParsePredicate(rule);
            ParsePredicateList(rule);
        }
    }

    void ParsePredicate(Rule *rule) {

        Predicate *predicate = new Predicate();
        predicate->SetName(tokenStorage.at(currentTokenIndex)->GetDescription());
        rule->SetBodyPredicate(predicate);
        Match(currentTokenIndex, "ID");
        Match(currentTokenIndex, "LEFT_PAREN");
        ParseParameter(rule, predicate);
        ParseParameterList(rule, predicate);
        Match(currentTokenIndex, "RIGHT_PAREN");
    }

    void ParsePredicate(Predicate *predicate) {

        Match(currentTokenIndex, "ID");
        Match(currentTokenIndex, "LEFT_PAREN");
        ParseParameter(predicate);
        ParseParameterList(predicate);
        Match(currentTokenIndex, "RIGHT_PAREN");
    }

    void ParseQuery() {
        //predicate Q_MARK
        Predicate *predicate = new Predicate();
        predicate->SetName(tokenStorage.at(currentTokenIndex)->GetDescription());
        queriesList.push_back(predicate);
        ParsePredicate(predicate);
        Match(currentTokenIndex, "Q_MARK");
    }

    void ParseQueryList() {
        if (tokenStorage.at(currentTokenIndex)->GetType() != "EOF") {
            ParseQuery();
            ParseQueryList();
        }
    }

    vector <Predicate*> GetSchemesList() {
        // << "size" << schemesList.size();
        return schemesList;
    }

    vector <Predicate*> GetFactsList() {
        //cout << "size" << factsList.size();
        return factsList;
    }

    vector <Predicate*> GetQueriesList() {
        //cout << "size" << queriesList.size();
        return queriesList;
    }

    vector <Rule*> GetRulesList() {
        return ruleLists;
    }
};
