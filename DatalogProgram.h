#pragma once
#include <vector>
/*The order must be: Schemes, then Facts, then Rules, then Queries

 There must be at least one Scheme and at least one Query
        There does not have to be any Facts or Rules

        datalogProgram  ->  SCHEMES COLON scheme schemeList
                            FACTS   COLON        factList
                            RULES   COLON        ruleList
                            QUERIES COLON query  queryList*/

class DatalogProgram {

private:
    vector<Predicate*> theSchemesList;
    vector<Predicate*> theFactsList;
    vector<Rule*> theRulesList;
    vector<Predicate*> theQueriesList;


public:
    DatalogProgram() {}
    ~DatalogProgram() {}

    void SetSchemesPredicate(vector<Predicate*> schemesList) {

        for (unsigned int i = 0; i < schemesList.size(); i++) {
            theSchemesList.push_back(schemesList.at(i));
        }

/*        for (unsigned int i = 0; i < theSchemesList.size(); i++) {
            cout << i << theSchemesList.at(i)->GetName() << endl;
        }*/

/*        for (unsigned int i = 0; i < theSchemesList.size(); i++) {
            theSchemesList.at(i)->PrintParameters();
        }*/

    }

    void SetFactsPredicate(vector<Predicate*> factsList) {

        for (unsigned int i = 0; i < factsList.size(); i++) {
            theFactsList.push_back(factsList.at(i));
        }
/*        for (int i = 0; i < theFactsList.size(); i++) {
            cout << i << theFactsList.at(i)->GetName() << endl;
        }*/
    }

    void SetQueriesPredicate(vector<Predicate*> queriesList) {

        for (unsigned int i = 0; i < queriesList.size(); i++) {
            theQueriesList.push_back(queriesList.at(i));
        }
/*        for (int i = 0; i < theQueriesList.size(); i++) {
            cout << theQueriesList.at(i) << endl;
        }*/
    }

    vector<Predicate*> GetVectorSchemes() {

        cout << theSchemesList.size() << endl;

        return theSchemesList;
    }

    vector<Predicate*> GetVectorFacts() {
        return theFactsList;
    }

    vector <Predicate*> GetVectorQueries() {
        return theQueriesList;
    }

};