#pragma once
#include "Header.h"
#include "Tuple.h"
#include <iostream>
#include <cstring>
#include <set>


class Relation {
private:
    string name = "";
    string nameHeader = "";
    string tupleValue = "";
    Header header;
    Header headHeader;
    set<Tuple> tuples;
    set<Tuple> newTuples;
    vector<string> values;
    vector<int> position;
    vector<int> indices;


public:

    void SetName(string theName) {
        name = theName;
    }

    void SetHeader(vector<Parameter *> params) {

        for (auto &param: params) {
            header.AddAttributes(param->GetName());
        }

    }

    void SetHeader(vector<char> myCharacters) {

        for (unsigned char i = 0; i < myCharacters.size(); i++) {
            string s;
            s.push_back(myCharacters.at(i));
            header.AddAttributes(s);
        }
    }

    void SetHeader(const Header &theHeader) {
        header = theHeader;
    }

    void SetHeadHeader(const Header &theHeadHeader) {
        headHeader = theHeadHeader;
    }

    void SetHeader(vector<string> attributes) {

        for (unsigned int i = 0; i < attributes.size(); i++) {
            header.AddAttributes(attributes.at(i));
        }

    }

    void DeleteHeader() {
        header.DeleteAllAttributes();
    }

    void SetNameHeadHeader(string theName) {
        nameHeader = theName;
    }

    void SetHeaderHead(vector<Parameter *> params) {
        for (auto &param: params) {
            headHeader.AddAttributes(param->GetName());
        }
    }

    void DeleteHeaderAttributes(int index) {

        header.DeleteAttributes(index);

    }

    string GetHeader(int index) {
        vector<string> name = header.GetAttributes();
        string myString;
        myString = name.at(index);
        return myString;
    }

    Header GetHeadHeader() {
        return headHeader;
    }

    Header GetHeader() {

        return header;
    }

    char GetHeaderCharacter(int index) {
        vector<string> name = header.GetAttributes();
        string myString;
        myString = name.at(index);
        char finalString = myString.at(0);
        return finalString;
    }

    unsigned int GetHeaderSize() {
        return header.GetAttributesSize();
    }

    void SetTuples(vector<Parameter *> params) {

        Tuple tuple;

        for (unsigned int i = 0; i < params.size(); i++) {
            tupleValue = params.at(i)->GetName();
            tuple.Add(params.at(i)->GetName());
        }
        tuples.insert(tuple);

        //cout << "size " << tuples.size();
    }

    void SetTuples(vector<string> newColumns) {
        Tuple tuple;

        for (unsigned int i = 0; i < newColumns.size(); i++) {
            tupleValue = newColumns.at(i);
            tuple.Add(newColumns.at(i));
        }
        tuples.insert(tuple);
    }

    void SetTuples(Tuple tuple) {
        tuples.insert(tuple);
        //cout << "size " << tuples.size();
    }


    void AddTuples(Relation *&relation) {

        Tuple newTuple;

        for (Tuple r: relation->GetTuples()) {
            newTuple = r;
            SetTuples(newTuple);
        }

    }

    void DeleteTuples(Tuple tuple) {

        auto it = tuples.find(tuple);
        tuples.erase(it);

    }

    void DeleteAllTuples() {
        tuples.clear();
    }

    void ResetTuples(Relation *&relation) {
        for (Tuple e: newTuples) {
            relation->SetTuples(e);
        }
    }

    string GetName() {
        return name;
    }

    set<Tuple> GetTuples() {
        return tuples;
    }

    set<Tuple> GetNewTuples() {
        return newTuples;
    }

    void PrintTuplesAtPosition(int index) {
        //cout << tuples.at(index);
    }

    void SetValuesVector(string name) {
        values.push_back(name);
    }

    void SetIndicesVector(int index) {
        indices.push_back(index);
    }

    vector<string> GetValuesVector() {
        return values;
    }

    string GetValuesVectorPosition(int index) {
        return values.at(index);
    }

    vector<int> GetIndicesVector() {
        return indices;
    }

    void PrintRelation() {
        vector<string> myAttributes = header.GetAttributes();
        for (unsigned int i = 0; i < myAttributes.size(); i++) {
            cout << myAttributes.at(i);
        }
        cout << endl;
        for (Tuple e: tuples) {
            e.toString();
        }
    }

    Relation *CreateQueries(Relation *newRelation) {

        string valueConstant = "";
        unsigned int indexConstant = 0;
        unsigned int indexVariableOne = 0;
        unsigned int indexVariableTwo = 0;

        for (unsigned int i = 0; i < newRelation->GetHeaderSize(); i++) {
            if (newRelation->GetHeaderCharacter(i) == '\'') {
                valueConstant = newRelation->GetHeader(i);
                indexConstant = i;
                newRelation = Select1(valueConstant, indexConstant, newRelation);
            }
            if (newRelation->GetHeaderCharacter(i) != '\'') {
                if (indexVariableOne < newRelation->GetHeaderSize()) {
                    indexVariableOne = i;
                    indexVariableTwo = i + 1;
                    newRelation = Select2(indexVariableOne, indexVariableTwo, newRelation);
                }
            }

            if (newRelation->GetHeaderSize() - 1 == i) {
                newRelation = Select3(newRelation);
            }
        }

/*        cout << endl;

        cout << "print my values " << endl;
        for (unsigned int i = 0; i < values.size(); i++) {
            cout << values.at(i);
        }

        cout << endl;

        cout << "after: " << endl;
        for (auto itr: newRelation->GetTuples()) {
            (itr).toString();
        }*/

        //TODO MAKE SURE TO TREAT RELATIION WITH EMPTY TUPLES
/*        if (newRelation->GetTuples().empty()) {
            cout << "NO" << endl;
        }*/

/*        for (auto itr: newRelation->GetTuples()) {
            for (unsigned int i = 0; i < GetHeaderSize(); i++) {
                if (newRelation->GetHeaderCharacter(i) != '\'') {
                    newRelation = Project(newRelation);
                    cout << "after: " << endl;
                    for (auto itr: newRelation->GetTuples()) {
                        (itr).toString();
                    }
                    break;
                } else {
                    cout << "NoPROJECT: " << endl;
                    for (auto itr: newRelation->GetTuples()) {
                        (itr).toString();
                    }
                    break;
                }
            }
            break;
        }*/

        return newRelation;

    }

    void PrintNewRelation(Relation *newRelation) {

        if (newRelation->GetTuples().empty()) {
            cout << newRelation->GetName();
            header.PrintAttributes();
            cout << " No" << endl;
        } else {
            cout << newRelation->GetName();
            header.PrintAttributes();
            cout << " Yes(" << newRelation->GetTuples().size() << ")" << endl;
            //TODO RENAME HEADER
            int index;
            for (unsigned int i = 0; i < newRelation->GetHeaderSize(); i++) {
                if (newRelation->GetHeaderCharacter(i) == '\'') {
                    index = i;
                    newRelation = newRelation->Rename(index, newRelation);
                }
            }

        }

/*        for (unsigned int i = 0; i < newRelation->GetValuesVector().size(); i++) {
            cout << newRelation->GetValuesVector().at(i);
        }

        for (unsigned int i = 0; i < newRelation->GetIndicesVector().size(); i++) {
            cout << newRelation->GetIndicesVector().at(i);
        }*/

        for (unsigned int i = 0; i < newRelation->GetValuesVector().size(); i++) {
            if (newRelation->GetHeaderCharacter(i) != '\'') {
                Tuple newTuple;
                set<Tuple>::iterator tupleItr;
                tupleItr = tuples.begin();
                while (tupleItr != tuples.end()) {
                    cout << "  ";
                    if (!newRelation->GetTuples().empty()) {
                        for (unsigned int i = 0; i < newRelation->GetValuesVector().size(); i++) {
                            if (i == newRelation->GetIndicesVector().size() - 1) {
                                cout << newRelation->GetValuesVector().at(i);
                                //header.PrintAttributesAtPosition(newRelation->GetIndicesVector().at(i));
                                cout << "=";
                                newTuple = *tupleItr;
                                newTuple.PrintTupleAtPosition(i);
                                break;
                            } else {
                                cout << newRelation->GetValuesVector().at(i);
                                //header.PrintAttributesAtPosition(newRelation->GetIndicesVector().at(i));
                                cout << "=";
                                newTuple = *tupleItr;
                                newTuple.PrintTupleAtPosition(i);
                            }
                            cout << ", ";
                        }
                    }
                    cout << endl;
                    tupleItr++;
                }

            }
            break;
        }

    }

    Relation *Select1(string valueConstant, unsigned int indexConstant, Relation *&relation) {
        //cout << "valueConstant " << valueConstant << endl;
        //cout << "indexConstant " << indexConstant << endl;

/*        cout << "before: " << endl;
        for (auto itr: relation->GetTuples()) {
            (itr).toString();
        }*/
        Tuple newTuple;
        set<Tuple>::iterator tupleItr;
        tupleItr = tuples.begin();
        while (tupleItr != tuples.end()) {
            newTuple = *tupleItr;
            if (!newTuple.FoundValue(valueConstant, indexConstant)) {
                tupleItr = tuples.erase(tupleItr);
            } else {
                tupleItr++;
            }
        }

        return relation;
    }

    Relation *Select2(int indexVariableOne, int indexVariableTwo, Relation *&relation) {

        // if vector is empty push the header into vector
        // else look up if you have seen this variable
        // if you have DO a select
        // else mark it
        string value = relation->GetHeader(indexVariableOne);
        if (values.empty()) {
            relation->SetValuesVector(value);
            relation->SetIndicesVector(indexVariableOne);
        } else {
            unsigned int i = 0;
            bool valueFound = false;
            while (i < relation->GetValuesVector().size()) {
                if (relation->GetValuesVector().at(i) != relation->GetHeader(indexVariableOne)) {
                    i++;
                } else {
                    valueFound = true;
                    Tuple newTuple;
                    set<Tuple>::iterator tupleItr;
                    tupleItr = tuples.begin();
                    while (tupleItr != tuples.end()) {
                        newTuple = *tupleItr;
                        if (!newTuple.FoundValue(i, indexVariableOne)) {
                            tupleItr = tuples.erase(tupleItr);
                            //cout << "here" << endl;
                            //May have to delete this following line because I changed it after passing Lab3
                            tupleItr = tuples.begin();
                        } else {
                            //This crashes during debug
                            tupleItr++;
                        }
                    }
                    valueFound = true;
                    i++;
                }
            }

            if (!valueFound) {
                relation->SetValuesVector(value);
                relation->SetIndicesVector(indexVariableOne);
            }

        }
        return relation;
    }

    Relation *Select3(Relation *&relation) {

        if (values.empty()) {
            return relation;
        } else {
            set<Tuple> temporaryTuples = relation->GetTuples();

            for (Tuple e: relation->GetTuples()) {
                relation->DeleteTuples(e);
            }

            Tuple newTuple;
            for (Tuple e: temporaryTuples) {
                vector<string> newTuples = e.FoundValue(indices);
                relation->SetTuples(newTuples);
            }
        }
        return relation;
    }

    void Project(Relation *&relation) {


        if (relation->GetHeader().GetAttributes().size() != relation->GetHeadHeader().GetAttributes().size()) {
            for (unsigned int i = 0; i < relation->GetHeadHeader().GetAttributes().size(); i++) {
                for (unsigned int j = 0; j < relation->GetHeader().GetAttributes().size(); j++) {
                    if (relation->GetHeadHeader().GetAttributes().at(i) ==
                        relation->GetHeader().GetAttributes().at(j)) {
                        position.push_back(j);
                    }
                }
            }


            set<Tuple> temporaryTuples = relation->GetTuples();

            for (Tuple e: relation->GetTuples()) {
                relation->DeleteTuples(e);
            }

            Tuple newTuple;
            for (Tuple e: temporaryTuples) {
                vector<string> newTuples = e.FoundValue(position);
                relation->SetTuples(newTuples);
            }
        }


    }

    //RENAME WILL CHANGE THE HEADER OF THE RELATION

    Relation *Rename(int index, Relation *relation) {

        relation->DeleteHeaderAttributes(index);

        return relation;
    }

    void Print(Relation *&relation) {

        //cout << "HERE:" << endl;
        for (Tuple x: relation->GetTuples()) {
            x.toString();

        }

    }




    // =======================================================================================================================

    //TODO Project 4

    Relation* CreateJoin(Relation *&relation, Relation *&newRelation, set<Tuple> Tuples) {

        Relation *finalRelation = new Relation();

        bool foundDuplicate = false;
        vector<pair<int, int>> myPair;


        //TODO COMBINE HEADER RELATION AND NEW RELATION
        vector<string> attributesRelation1 = relation->GetHeader().GetAttributes();
        vector<string> attributesRelation2 = newRelation->GetHeader().GetAttributes();
        vector<string> attributesCombine;

        for(unsigned int i = 0; i < attributesRelation1.size(); i++){
            for(unsigned int j = 0; j < attributesRelation2.size(); j++){
                if(attributesRelation1.at(i) == attributesRelation2.at(j)){
                    myPair.push_back((make_pair(i, j)));
                    foundDuplicate = true;
                }
            }
        }

        attributesCombine = attributesRelation1;

        for(unsigned int i = 0; i < attributesRelation2.size(); i++){
            attributesCombine.push_back(attributesRelation2.at(i));
        }

        finalRelation->SetHeader(attributesCombine);


        //TODO JOIN TUPLE IF IT CAN JOIN
        vector<string>valuesRelation1;
        vector<string>valuesRelation2;
        vector<string> valuesCombine;

        for(Tuple e : relation->GetTuples()){
            Tuple tupleFound1 = e;
            valuesRelation1 = tupleFound1.GetVectorValues();
            for(Tuple t : newRelation->GetTuples()){
                Tuple tupleFound2 = t;
                valuesRelation2 = tupleFound2.GetVectorValues();
                if(!foundDuplicate){
                     valuesCombine = CombineTuples(valuesCombine, valuesRelation1, valuesRelation2);
                     finalRelation->SetTuples(valuesCombine);
                } else {
                    bool matching = true;
                    for(unsigned int i = 0; i < myPair.size(); i++){
                        if(valuesRelation1.at(myPair.at(i).first) == valuesRelation2.at(myPair.at(i).second)){
                            continue;
                        } else {
                            matching = false;
                        }
                    }
                    if(matching){
                        valuesCombine = CombineTuples(valuesCombine, valuesRelation1, valuesRelation2);
                        finalRelation->SetTuples(valuesCombine);
                    }
                    /*if(valuesRelation1.at(myPair.first) == valuesRelation2.at(myPair.second)){
                        valuesCombine = CombineTuples(valuesCombine, valuesRelation1, valuesRelation2);
                        finalRelation->SetTuples(valuesCombine);
                    }*/
                   // cout << " TRUE AGAIN " << endl;
                }
              //  cout << "AGAIN" << endl;
            }
           // cout << "ALMOST OUT " << endl;
        }
     //  cout << "OUT" << endl;

        //TODO TRANSFER ALL INFORMATION FROM RELATION1 TO FINAL RELATION

        string nameHeadHeader = relation->GetName();
        finalRelation->SetName(nameHeadHeader);
        Header headHeader = relation->GetHeadHeader();
        finalRelation->SetHeadHeader(headHeader);
        //cout << "HERE" << endl;


        relation = finalRelation;
        return relation;
    }

    vector<string> CombineTuples(vector<string> &valuesCombine, vector<string> &valuesRelation1, vector<string> &valuesRelation2) {

        valuesCombine = valuesRelation1;

        for(unsigned int i = 0; i < valuesRelation2.size(); i++){
            valuesCombine.push_back(valuesRelation2.at(i));
        }


        return valuesCombine;
    }


    void Select(Relation *&relation, Header header , string name) {

        vector<string> attributesMainHeader = header.GetAttributes();
        vector<unsigned int> duplicateColumn;
        unsigned int index = 0;

        //TODO FIND THE COLUMN WE NEED TO ELIMINATE
      /*  for(unsigned int i = 0; i < relation->GetHeadHeader().GetAttributes().size(); i++) {
            for (unsigned int j = 0; j < relation->GetHeader().GetAttributes().size(); j++){
                if(relation->GetHeadHeader().GetAttributes().at(i) == relation->GetHeader().GetAttributes().at(j)){
                    duplicateColumn.push_back(i);
                }
            }
        }*/

      for(unsigned int i = 0; i < relation->GetHeader().GetAttributes().size(); ){
          if(FoundDuplicate(i, relation->GetHeader().GetAttributes().at(i), relation->GetHeader().GetAttributes())) {
              duplicateColumn.push_back(i);

              Relation *eliminateColumn = new Relation();
              //TODO ELIMINATE COLUMN FROM HEADER
              vector<string> myHeader;
              if(!duplicateColumn.empty()){
                  myHeader = relation->GetHeader().GetAttributes();
                  for(unsigned int j = 0; j < myHeader.size(); j++){
                      if(j == duplicateColumn.at(index)){
                          myHeader.erase(myHeader.begin()+j);
                      }
                  }
              }
              if(!duplicateColumn.empty()){
                  relation->DeleteHeader();
                  relation->SetHeader(myHeader);
              }


              //TODO ElIMINATE COLUMN FROM TUPLE
              if(!duplicateColumn.empty()){
                  vector<string> values;
                  for(Tuple e : relation->GetTuples()){
                      Tuple foundTuple = e;
                      values = foundTuple.GetVectorValues();
                      for(unsigned int j = 0; j < values.size(); j++){
                          if(j == duplicateColumn.at(index)){
                              values.erase(values.begin()+j);
                          }
                      }
                      eliminateColumn->SetTuples(values);
                  }
              }

              if(!duplicateColumn.empty()){
                  relation->DeleteAllTuples();
                  for(Tuple e : eliminateColumn->GetTuples()){
                      Tuple foundTuple = e;
                      relation->SetTuples(foundTuple);
                  }
              }


              duplicateColumn.clear();
          } else {
              i++;
          }
      }


/*        for(unsigned int i = 0; i < relation->GetHeader().GetAttributes().size();i++){
            int index = 0;
            while(index != relation->GetHeader().GetAttributes().size() - 1){
                if(relation->GetHeader().GetAttributes().at(i) == relation->GetHeader().GetAttributes().at(index)){
                    duplicateColumn.push_back(i);
                    index++;
                } else {
                    index++;
                }
            }
        }*/

        //cout << "MYDUPLCIATE" << endl;
        /*for(unsigned int i = 0; i < duplicateColumn.size(); i++){
            cout <<duplicateColumn.at(i) << endl;
        }*/

/*        //TODO ElIMINATE COLUMN FROM TUPLE
        Relation *eliminateColumn = new Relation();
        if(!duplicateColumn.empty()){
            vector<string> values;
            for(Tuple e : relation->GetTuples()){
                Tuple foundTuple = e;
                values = foundTuple.GetVectorValues();
                for(unsigned int i = 0; i < values.size(); i++){
                    if(i == duplicateColumn.at(1)){
                        values.erase(values.begin()+i);
                    }
                }
                eliminateColumn->SetTuples(values);
            }
        }

        if(!duplicateColumn.empty()){
            relation->DeleteAllTuples();
            for(Tuple e : eliminateColumn->GetTuples()){
                Tuple foundTuple = e;
                relation->SetTuples(foundTuple);
            }
        }

        //TODO ELIMINATE COLUMN FROM HEADER
        vector<string> myHeader;
        if(!duplicateColumn.empty()){
            myHeader = relation->GetHeader().GetAttributes();
            for(unsigned int i = 0; i < myHeader.size(); i++){
                if(i == duplicateColumn.at(1)){
                    myHeader.erase(myHeader.begin()+i);
                }
            }
        }

        if(!duplicateColumn.empty()){
            relation->DeleteHeader();
            relation->SetHeader(myHeader);
        }*/


        //TODO CHOOSE HEADER WE NEED


        //TODO DEBUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUG HERE
        vector <int> positionToKeep;
        vector<string> valuesHeadHeader = relation->GetHeadHeader().GetAttributes();
        vector<string> valuesHeader = relation->GetHeader().GetAttributes();
        for(unsigned int i = 0; i < valuesHeadHeader.size(); i++){
            for(unsigned int j = 0; j < valuesHeader.size(); j++){
                if(valuesHeadHeader.at(i) == valuesHeader.at(j)){
                    positionToKeep.push_back(j);
                }
            }
        }

        /*for(unsigned int i = 0; i < positionToKeep.size(); i++){
            cout << positionToKeep.at(i);
        }*/

        //TODO ELIMINATE POSITION WE DON'T NEED IN  COMPARED TO HEADHEADER
        vector<string> finalHeader = relation->GetHeader().GetAttributes();
        vector<string> secondFinalHeader;
        for(unsigned int i = 0; i < finalHeader.size(); i++){
            if(FoundPosition(i, positionToKeep)) {
                secondFinalHeader.push_back(finalHeader.at(i));
            }
        }
        relation->DeleteHeader();
        relation->SetHeader(secondFinalHeader);

        //cout << "HERE BUDDY" << endl;


        //TODO ELIMINATE POSITION IN TUPLES THAT WE DONT NEED
        vector<string> valuesTuple;
        vector <string> myFinalValues;

        Relation *finalTuples = new Relation();
        for(Tuple e : relation->GetTuples()){
            Tuple foundTuple = e;
            valuesTuple = foundTuple.GetVectorValues();
            for(unsigned int i = 0; i < valuesTuple.size(); i++){
                if(FoundPosition(i, positionToKeep)){
                    myFinalValues.push_back(valuesTuple.at(i));
                }
            }
            finalTuples->SetTuples(myFinalValues);
            myFinalValues.clear();
        }

        relation->DeleteAllTuples();
        for(Tuple e : finalTuples->GetTuples()){
            Tuple foundTuple = e;
            relation->SetTuples(foundTuple);
        }

        //cout << "DEBUG HEREEE" << endl;


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    }

    bool FoundPosition(int index, vector<int> positionToKeep) {

        bool valFound = false;



        for (unsigned int i = 0; i < positionToKeep.size(); i++) {
            if (index == positionToKeep.at(i)) {
                valFound = true;
                return valFound;
            }
        }

        return valFound;

    }


    void PrintPrint(Relation *relation, Header header) {

        vector<string> attributesMainHeader = header.GetAttributes();

        for (Tuple e: relation->GetTuples()) {
            Tuple foundTuple = e;
            values = foundTuple.GetVectorValues();
            //cout << "Here";
            for (unsigned int i = 0; i < attributesMainHeader.size(); i++) {
                int index = 0;
                //ELSE
                if(i != attributesMainHeader.size()-1 && attributesMainHeader.size() != 1){
                    if(i == 0 ){
                        cout << "  ";
                    }
                    cout << attributesMainHeader.at(i) << "=" << values.at(i) <<", ";
                    index++;
                } else if(attributesMainHeader.size() == 1){
                    cout << "  ";
                    cout << attributesMainHeader.at(i) << "=" << values.at(i);
                    index++;
                } else {
                    cout << attributesMainHeader.at(i) << "=" << values.at(i);
                    index++;
                }

            }
            cout << endl;

        }
    }


    Relation* Select2(Relation *&relation, Header header , string name, bool select) {


        //TODO MODIFY ORDER TUPLES
        vector<string> headHeader1 = relation->GetHeadHeader().GetAttributes();
        vector<string> header2 = relation->GetHeader().GetAttributes();
        vector<int> reorderPosition;

        for(unsigned int i = 0; i < headHeader1.size(); i++){
            for(unsigned int j = 0; j < header2.size(); j++){
                if(headHeader1.at(i) == header2.at(j)){
                    reorderPosition.push_back(j);
                }
            }
        }

        vector<string>valuesAgain;
        vector<string>finalValues;
        Relation *finishTuple = new Relation();
        for(Tuple e : relation->GetTuples()) {
            Tuple foundTuple = e;
            valuesAgain = foundTuple.GetVectorValues();
            for(unsigned int i = 0; i < reorderPosition.size(); i++){
                finalValues.push_back(valuesAgain.at(reorderPosition.at(i)));
            }
            finishTuple->SetTuples(finalValues);
            finalValues.clear();
        }

        relation->DeleteAllTuples();
        for(Tuple e : finishTuple->GetTuples()){
            Tuple foundTuple = e;
            relation->SetTuples(foundTuple);
        }

        return relation;

    }

    bool FoundDuplicate(unsigned int index, string value, vector<string> values){
        bool foundDuplicate = false;

        for(unsigned int i = 0; i < values.size(); i++){
            if(i != index){
                if(values.at(i) == value){
                    foundDuplicate = true;
                    return foundDuplicate;
                }
            }
        }

        return foundDuplicate;
    }


};





