#pragma once

class Header {
private:
    vector <string> attributes;
public:
    Header(){}
    ~Header(){}

    void AddAttributes(string name) {
        attributes.push_back(name);
    }

    vector<string> GetAttributes() const {
        return attributes;
    }

    unsigned int GetAttributesSize() {
        return attributes.size();
    }

    vector<string> DeleteAttributes(int index) {
        attributes.erase(attributes.begin()+index);

        return attributes;
    }

    void DeleteAllAttributes() {
        attributes.clear();
    }

    int AttributesSize() {
        return attributes.size();
    }

    void PrintAttributes() {
        stringstream ss;
        for (unsigned int i = 0; i < attributes.size(); i ++) {
            if(i == 0) {
                ss << "(" << attributes.at(i) << ",";
            }
            if (i > 0 && i < attributes.size()-1) {
                ss << attributes.at(i) << ",";
            }
            if (i == attributes.size()-1) {
                ss << attributes.at(i) << ")?";
            }
        }

        cout << ss.str();
    }

    void PrintAttributesAtPosition(int index) {
        cout << attributes.at(index);
    }




};
