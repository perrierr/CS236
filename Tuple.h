#pragma once

class Tuple {
private:
    vector <string> values;

public:
    bool operator < (const Tuple &rhs) const {
        return values < rhs.values;
    }

    vector<string> GetVectorValues() {
        return values;
    }

    vector<string> Delete(vector<int> position) {
        while(!position.empty()){
            values.erase(values.begin()+position.at(0));
            position.erase(position.begin()+0);
        }

        return values;

    }

    string GetValue(int index) {
        return values.at(index);
    }

    void Add(string name) {
        values.push_back(name);
    }


    string GetValues() {
        stringstream ss;
        for (unsigned int i = 0; i < values.size(); i++) {
            ss << values.at(i) << endl;
        }

        return ss.str();
    }

    void toString() const{
        for (unsigned int i = 0; i < values.size(); i++) {
            cout << values.at(i);
        }
        cout << endl;
    }

    void PrintTupleAtPosition(int index) {
        cout << values.at(index);
    }

    bool FoundValue(string value, unsigned int index) const {

        bool valueFound = false;
        for (unsigned int i = 0; i < values.size(); i++) {
            if (i == index) {
                if (values.at(index) == value) {
                    valueFound = true;
                    return valueFound;
                } else {
                    return valueFound;
                }
            }
        }

        return valueFound;
    }

    bool FoundValue(unsigned int index1, unsigned int index2) const {

        bool valueFound = false;
        if(values.at(index1) == values.at(index2)) {
            valueFound = true;
            return valueFound;
        } else {
            return valueFound;
        }

        return valueFound;
    }

    vector <string> FoundValue(vector<int> &indices) {

        vector <string> selectColumn;

        for(unsigned int i = 0; i < indices.size(); i++) {
            selectColumn.push_back(values.at(indices.at(i)));
        }
        return selectColumn;
    }

    bool Check(vector <int> indices) const {
        bool valueFound = false;
        if(values.at(indices.at(0)) == values.at(indices.at(1))) {
            valueFound = true;
            return valueFound;
        }
        return valueFound;
    }

};
