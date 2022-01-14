#pragma once
#include "Parameter.h"
#include <sstream>

using namespace std;


class Predicate {
private:
    string theName;

public:
    vector <Parameter*> parameters;
public:

    Predicate(){
        theName = "";
    }

    ~Predicate(){}


    void SetName(string name) {
        theName = name;
    }

    void Add(Parameter *params) {
        parameters.push_back(params);
    }

    vector<Parameter*> GetParameters() {
        return parameters;
    }

    void PrintParameters() {
        for (unsigned int i = 0; i < parameters.size(); i++) {
            cout << parameters.at(i)->GetName();
        }
        cout << endl;
    }

    string GetName() {
        return theName;
    }

    int GetNameSize() {
        return theName.size();
    }

    string toString() {

        stringstream ss;
        ss << theName << "(";
        for (unsigned int i = 0; i < parameters.size(); i++) {
            if((i+1) == parameters.size()) {
                ss  << parameters.at(i)->GetName() << ")";
            } else {
                ss  << parameters.at(i)->GetName() << ",";
            }
        }
        string myReturn = ss.str();
        return myReturn;
    }


    void PrintSchemes() {

        stringstream ss;
        ss << theName << "(";
        for (unsigned int i = 0; i < parameters.size(); i++) {
            if((i+1) == parameters.size()) {
                ss  << parameters.at(i)->GetName() << ")";
            } else {
                ss  << parameters.at(i)->GetName() << ",";
            }
        }
        cout << ss.str();
    }

    void PrintQueries() {
        stringstream ss;
        ss << theName << "(";
        for (unsigned int i = 0; i < parameters.size(); i++) {
            if((i+1) == parameters.size()) {
                ss  << parameters.at(i)->GetName() << ")";
            } else {
                ss  << parameters.at(i)->GetName() << ",";
            }
        }

        ss << "?";
        cout << ss.str();
    }

    void PrintFacts() {
        stringstream ss;
        ss << theName << "(";
        for (unsigned int i = 0; i < parameters.size(); i++) {
            if((i+1) == parameters.size()) {
                ss  << parameters.at(i)->GetName() << ")";
            } else {
                ss  << parameters.at(i)->GetName() << ",";
            }
        }

        ss << ".";
        cout << ss.str();
    }
};