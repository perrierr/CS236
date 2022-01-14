#pragma once
#include "Relation.h"
#include <map>
#include "Graph.h"


class Database {
private:

    int before = -1;
    int after = -2;
    set<Tuple> toPrintTuples;
    set <Tuple> finalTuples;
    set<Tuple> newTuples;
    unsigned int check = 0;


public:
    map<string, Relation*> tables;

    void CreateMapKeyHeader(vector <Predicate*> schemesList) {
        for (auto & i : schemesList) {
            auto* relation = new Relation;
            relation->SetName(i->GetName());
            relation->SetHeader(i->GetParameters());
            //relation->PrintHeader();
            //relation->PrintName();
            tables.insert(std::pair<string, Relation*>(relation->GetName(),relation));
        }
/*        cout << "myMap contains:\n";
        for (itr = tables.begin(); itr!= tables.end(); itr++) {
            cout << "Key" << itr->first << endl;
            cout << "relation ";
            itr->second->PrintRelation();
        }*/
    }

    void AddTuples (vector<Predicate*> factsList) {
        for (unsigned int i = 0; i < factsList.size(); i++) {
            auto itr = tables.find(factsList.at(i)->GetName());
            itr->second->SetTuples(factsList.at(i)->GetParameters());
        }

/*        cout << "myMap contains:\n";
        for (auto itr = tables.begin(); itr != tables.end(); itr++) {
            cout << "Key: " << itr->first << endl;
            cout << "Relation: ";
            itr->second->PrintRelation();
        }*/
    }

    void CreateQueries(vector<Predicate*> queriesList) {

        for(auto & i : queriesList) {
            auto *newRelation = new Relation();
            newRelation->SetName(i->GetName());
            newRelation->SetHeader(i->GetParameters());

            // find the table for the given name
            auto itr = tables.find(i->GetName());

            //cout << "Found Tuples:" << endl;
            // get tuple for the found table
            set<Tuple> foundTuples = itr->second->GetTuples();
            set<Tuple>::iterator tupleItr;
            for (tupleItr = foundTuples.begin(); tupleItr != foundTuples.end(); tupleItr++) {
                Tuple foundTuple = *tupleItr;

                //foundTuple.toString();
                newRelation->SetTuples(foundTuple);
            }

            newRelation = newRelation->CreateQueries(newRelation);
            newRelation->PrintNewRelation(newRelation);
        }
    }

    void OptimizeRules(vector<Rule*> rules){

        Graph reverseGraph;

        reverseGraph.SetDependencyGraph(rules);

        reverseGraph.SetReversedGraph(rules);

        long unsigned int valuesVisited = 0;

        while (valuesVisited != rules.size()){
           valuesVisited = reverseGraph.CreatePostOrder(rules);
        }

        reverseGraph.ReversePostOrder();

        //TODO TEST CASE
        //reverseGraph.toPrintPostOrder();

        //TODO CREATE STRONGLY CONNECTED COMPONENTS
        reverseGraph.CreateSCC();

        cout << "Rule Evaluation" << endl;
        while(reverseGraph.GetSCCSize() != 0) {
            //TODO GET STRONGLY CONNECTED COMPONENTS
            set <int> buff = reverseGraph.GetSCC();

            int numberOfWhileLoop = 0;
            const int toCheck = buff.size();
            int finalToCheck;
            bool doneFirstSelect = false;
            Rule *LoopRule = new Rule();

            cout << "SCC: ";

            check = 0;
            for(auto it = buff.begin(); it != buff.end(); it++) {
                unsigned int iteration = buff.size();
                if(buff.size() == 1) {
                    cout << "R" << *it;
                } else if (check < iteration-1) {
                    cout << "R" << *it << ",";
                    check++;
                } else {
                    cout << "R" << *it;
                }

            }
            cout << endl;
            do {
                numberOfWhileLoop++;
                finalToCheck = 0;
                int getPosition = 0;
                for (auto & j: rules) {
                    for (auto itr = buff.begin(); itr != buff.end(); itr++) {
                        if(getPosition == *itr) {
                            LoopRule = j;
                            auto itr = tables.find(j->GetHeadPredicate()->GetName());
                            before = itr->second->GetTuples().size();
                            // cout << "BEFORE " << before << endl;
                            auto *relation = new Relation();
                            //Remember the first size

                            relation->SetName(j->GetHeadPredicate()->GetName());
                            //cout << "DEBUG HERE " << endl;
                            relation->SetHeaderHead(j->GetHeadPredicate()->GetParameters());
                            vector < Predicate * > bodyPredicates = j->GetBodyPredicate();
                            for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
                                if (i == 0) {
                                    relation->SetHeader(j->GetBodyPredicate().at(i)->GetParameters());
                                    auto itr = tables.find(j->GetBodyPredicate().at(i)->GetName());
                                    set <Tuple> mySet = itr->second->GetTuples();
                                    set<Tuple>::iterator myItr;
                                    Tuple foundTuple;
                                    for (myItr = mySet.begin(); myItr != mySet.end(); myItr++) {
                                        foundTuple = *myItr;
                                        relation->SetTuples(foundTuple);
                                    }
                                    //special SELECT ON STRING
                                    for(unsigned int i = 0; i < relation->GetHeader().GetAttributes().size(); i++){
                                        if(relation->GetHeaderCharacter(i) == '\''){
                                            string valueConstant = relation->GetHeader(i);
                                            int indexConstant = i;
                                            relation = relation->Select1(valueConstant, indexConstant, relation);
                                        }
                                    } //END OF SPECIAL SELECT
                                } else {
                                    auto *newRelation = new Relation();
                                    auto itr = tables.find(bodyPredicates.at(i)->GetName());
                                    newRelation->SetHeader(bodyPredicates.at(i)->GetParameters());
                                    set <Tuple> mySecondSet = itr->second->GetTuples();
                                    set<Tuple>::iterator myItr;
                                    Tuple foundTuple;
                                    for (myItr = mySecondSet.begin(); myItr != mySecondSet.end(); myItr++) {
                                        foundTuple = *myItr;
                                        newRelation->SetTuples(foundTuple);
                                    }
                                    //SPECIAL SELECT ON STRING
                                    for(unsigned int i = 0; i < newRelation->GetHeader().GetAttributes().size(); i++){
                                        if(newRelation->GetHeaderCharacter(i) == '\''){
                                            string valueConstant = newRelation->GetHeader(i);
                                            int indexConstant = i;
                                            newRelation = newRelation->Select1(valueConstant, indexConstant, newRelation);
                                        }
                                    } //END OF SPECIAL SELECT


                                    relation = relation->CreateJoin(relation, newRelation, itr->second->GetTuples());
                                    if(i == bodyPredicates.size() - 1) {
                                        if(relation->GetHeader().GetAttributes().size() != relation->GetHeadHeader().GetAttributes().size()) {
                                            //TODO DEBUG HEREEEEE!!! NEED SOMETHING THAT TAKES ALL THE PAIR IN THE HEADER.. NOT JUST ONE
                                            //TODO MAKE IT RETURN A TRUE OR FALSE
                                            relation->Select(relation, itr->second->GetHeader(), itr->second->GetName());
                                            doneFirstSelect = true;

                                        }
                                    }
                                }
                            }

                            //cout << "HERE";
                            relation = relation->Select2(relation, itr->second->GetHeader(), itr->second->GetName(), doneFirstSelect);

                            auto iterator = tables.find(j->GetHeadPredicate()->GetName());
                            set<Tuple> tuples = iterator->second->GetTuples();

                            for(Tuple e : relation->GetTuples()) {
                                Tuple foundTuple = e;
                                if(tuples.find(foundTuple) != tuples.end()){
                                    relation->DeleteTuples(foundTuple);
                                }
                            }
                            //cout << "REACHING HERE: " << endl;
                            if(relation->GetTuples().empty()){
                                j->PrintRules();
                                cout << endl;
                                finalToCheck++;
                            } else {
                                j->PrintRules();
                                cout << endl;
                                relation->PrintPrint(relation, itr->second->GetHeader());
                            }


                            //TODO GET NEW SIZE OF MAP
                            after = itr->second->GetTuples().size();

                            //TODO ADD TUPLES TO MY MAP
                            for (Tuple e: relation->GetTuples()) {
                                Tuple foundTuple = e;
                                itr->second->SetTuples(foundTuple);
                            }
                            //cout << "BEFORE " << before << "AFTER " << after << endl;
                            //cout << "TOCHECK " << toCheck << "FINAL TO CHECK " << finalToCheck << endl;


                        }
                    }

                    getPosition++;


                } //end of main forLoop

                bool selfLoop = false;
                if(buff.size() == 1) {
                    for(unsigned int i = 0; i < LoopRule->GetBodyPredicate().size(); i++){
                        if(LoopRule->GetHeadPredicate()->GetName() == LoopRule->GetBodyPredicate().at(i)->GetName()){
                            selfLoop = true;
                        }
                    }
                }

                if(buff.size() == 1 && !selfLoop){
                    finalToCheck = toCheck;
                }



            } while (toCheck != finalToCheck);
            //cout << endl;
            //cout << "Schemes populated after " << numberOfWhileLoop << " passes through the Rules." << endl;
            //cout << endl;

            cout << numberOfWhileLoop << " passes: ";
            check = 0;
            for(auto it = buff.begin(); it != buff.end(); it++) {
                unsigned int iteration = buff.size();
                if(buff.size() == 1) {
                    cout << "R" << *it;
                } else if (check < iteration-1) {
                    cout << "R" << *it << ",";
                    check++;
                } else {
                    cout << "R" << *it;
                }

            }
            cout << endl;




        }// end of while loop for reverseGraph
        cout << endl;
        cout << "Query Evaluation" << endl;

    }

    void CreateRules(vector<Rule*> rules) {

        int numberOfWhileLoop = 0;
        const int toCheck = rules.size();
        int finalToCheck;
        bool doneFirstSelect = false;

        cout << "Rule Evaluation" << endl;
        do {
            numberOfWhileLoop++;
            finalToCheck = 0;
            for (auto & j: rules) {
                auto itr = tables.find(j->GetHeadPredicate()->GetName());
                before = itr->second->GetTuples().size();
               // cout << "BEFORE " << before << endl;
                auto *relation = new Relation();
                //Remember the first size

                relation->SetName(j->GetHeadPredicate()->GetName());
                //cout << "DEBUG HERE " << endl;
                relation->SetHeaderHead(j->GetHeadPredicate()->GetParameters());
                vector < Predicate * > bodyPredicates = j->GetBodyPredicate();
                for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
                    if (i == 0) {
                        relation->SetHeader(j->GetBodyPredicate().at(i)->GetParameters());
                        auto itr = tables.find(j->GetBodyPredicate().at(i)->GetName());
                        set <Tuple> mySet = itr->second->GetTuples();
                        set<Tuple>::iterator myItr;
                        Tuple foundTuple;
                        for (myItr = mySet.begin(); myItr != mySet.end(); myItr++) {
                            foundTuple = *myItr;
                            relation->SetTuples(foundTuple);
                        }
                        //special SELECT ON STRING
                        for(unsigned int i = 0; i < relation->GetHeader().GetAttributes().size(); i++){
                            if(relation->GetHeaderCharacter(i) == '\''){
                                string valueConstant = relation->GetHeader(i);
                                int indexConstant = i;
                                relation = relation->Select1(valueConstant, indexConstant, relation);
                            }
                        } //END OF SPECIAL SELECT
                    } else {
                        auto *newRelation = new Relation();
                        auto itr = tables.find(bodyPredicates.at(i)->GetName());
                        newRelation->SetHeader(bodyPredicates.at(i)->GetParameters());
                        set <Tuple> mySecondSet = itr->second->GetTuples();
                        set<Tuple>::iterator myItr;
                        Tuple foundTuple;
                        for (myItr = mySecondSet.begin(); myItr != mySecondSet.end(); myItr++) {
                            foundTuple = *myItr;
                            newRelation->SetTuples(foundTuple);
                        }
                        //SPECIAL SELECT ON STRING
                        for(unsigned int i = 0; i < newRelation->GetHeader().GetAttributes().size(); i++){
                            if(newRelation->GetHeaderCharacter(i) == '\''){
                                string valueConstant = newRelation->GetHeader(i);
                                int indexConstant = i;
                                newRelation = newRelation->Select1(valueConstant, indexConstant, newRelation);
                            }
                        } //END OF SPECIAL SELECT


                        relation = relation->CreateJoin(relation, newRelation, itr->second->GetTuples());
                        if(i == bodyPredicates.size() - 1) {
                            if(relation->GetHeader().GetAttributes().size() != relation->GetHeadHeader().GetAttributes().size()) {
                                //TODO DEBUG HEREEEEE!!! NEED SOMETHING THAT TAKES ALL THE PAIR IN THE HEADER.. NOT JUST ONE
                                //TODO MAKE IT RETURN A TRUE OR FALSE
                                relation->Select(relation, itr->second->GetHeader(), itr->second->GetName());
                                doneFirstSelect = true;

                            }
                        }
                    }
                }

                //cout << "HERE";
                relation = relation->Select2(relation, itr->second->GetHeader(), itr->second->GetName(), doneFirstSelect);

                auto iterator = tables.find(j->GetHeadPredicate()->GetName());
                set<Tuple> tuples = iterator->second->GetTuples();

                for(Tuple e : relation->GetTuples()) {
                    Tuple foundTuple = e;
                    if(tuples.find(foundTuple) != tuples.end()){
                        relation->DeleteTuples(foundTuple);
                    }
                }
                //cout << "REACHING HERE: " << endl;
                if(relation->GetTuples().empty()){
                    j->PrintRules();
                    cout << endl;
                    finalToCheck++;
                } else {
                    j->PrintRules();
                    cout << endl;
                    relation->PrintPrint(relation, itr->second->GetHeader());
                }


                //TODO GET NEW SIZE OF MAP
                after = itr->second->GetTuples().size();

                //TODO ADD TUPLES TO MY MAP
                for (Tuple e: relation->GetTuples()) {
                    Tuple foundTuple = e;
                    itr->second->SetTuples(foundTuple);
                }
                //cout << "BEFORE " << before << "AFTER " << after << endl;
                //cout << "TOCHECK " << toCheck << "FINAL TO CHECK " << finalToCheck << endl;

            }

        } while (toCheck != finalToCheck);
        cout << endl;
        cout << "Schemes populated after " << numberOfWhileLoop << " passes through the Rules." << endl;
        cout << endl;
        cout << "Query Evaluation" << endl;
    }

};
