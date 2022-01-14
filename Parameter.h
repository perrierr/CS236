#pragma once
#include "Token.h"
#include "Predicate.h"

class Parameter {
protected:
    string theName;

public:
    Parameter() {
        theName = "";
    }

    ~Parameter() {}


    void Set(string name) {
        theName = name;
    }

    string GetName() {
        return theName;
    }
};


