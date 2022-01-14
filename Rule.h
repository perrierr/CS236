#pragma once
#include "Predicate.h"


class Rule {

private:
    Predicate* headPredicate;
    vector<Predicate *> bodyPredicates;
public:
    Rule() {}

    ~Rule() {}

    void SetHeadPredicate(Predicate *predicate) {
        headPredicate = predicate;
    }

    void SetBodyPredicate(Predicate *predicate) {
        bodyPredicates.push_back(predicate);
    }


    void PrintRules() {

        stringstream ss;

            ss << headPredicate->GetName() << "(";
            vector <Parameter*> parameters = headPredicate->GetParameters();
            for (unsigned int i = 0; i < parameters.size(); i++) {
                if (i == (parameters.size()-1)) {
                   ss << parameters.at(i)->GetName() << ")";
                } else
                ss << parameters.at(i)->GetName() << ",";
            }


        ss << " :- ";

        for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
            ss << bodyPredicates.at(i)->GetName() << "(";
            vector<Parameter *> parameters = bodyPredicates.at(i)->GetParameters();
            if (i == bodyPredicates.size() -1) {
                for (unsigned int i = 0; i < parameters.size(); i++) {
                    if (i == (parameters.size()-1)) {
                        ss << parameters.at(i)->GetName() << ").";
                    }
                    else
                        ss << parameters.at(i)->GetName() << ",";
                }

            }
            else {
                for (unsigned int i = 0; i < parameters.size(); i++) {
                    if (i == (parameters.size()-1)) {
                        ss << parameters.at(i)->GetName() << "),";
                    }
                    else
                        ss << parameters.at(i)->GetName() << ",";
                }
            }
        }

        cout << ss.str();
    }

    Predicate* GetHeadPredicate() {
        return headPredicate;
    }


    int GetPosition() {

        for(unsigned int i = 0; i < bodyPredicates.size(); i++){
            return i;
        }
    }

    vector<Predicate*> GetBodyPredicate() {
        return bodyPredicates;
    }

};