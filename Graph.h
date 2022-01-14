#pragma once
#include <map>
#include <stack>

class Graph {
private:
    int keyNumber;
    int valueForKeyNumber;
    map<int,set<int>> dependencyGraph;
    map<int,set<int>> reversedGraph;
    stack<int> theStack;
    vector <int> valuesVisitedVec;
    vector<int> postOrderVec;
    vector<int> reverseOrderVec;
    vector<set<int>> DFSTreeSCC;
    vector <int> v;


public:
    void SetDependencyGraph(vector <Rule*> rules) {

        //TODO SET UP THE KEY OF THE MAP WITH ALL THE RULES
        keyNumber = 0;
        for (auto &j : rules) {
            dependencyGraph[keyNumber];
            keyNumber++;
            j->GetHeadPredicate();
        }

        //TODO TEST CASE
/*        auto iter = dependencyGraph.begin();
        while (iter != dependencyGraph.end()) {
            cout << "R" << iter->first << ",";
            ++iter;
        }*/

        //TODO SET UP THE VALUE(S) FOR EACH KEY --> DEPENDENCY
        valueForKeyNumber = 0;
        int indexRule = 0;
        for (auto &i: rules) {
            vector<Predicate *> bodyPredicate = i->GetBodyPredicate();
            for (auto &j : bodyPredicate){
                for(auto &k : rules){
                    if(j->GetName() == k->GetHeadPredicate()->GetName()) {
                        auto itr = dependencyGraph.find(indexRule);
                        itr->second.insert(valueForKeyNumber);
                    }
                    valueForKeyNumber++;
                }
                valueForKeyNumber = 0;
            }
            indexRule++;
        }

        //TODO TEST CASE
        cout << "Dependency Graph " << endl;
        for(auto const& pair : dependencyGraph) {
            cout << "R" << pair.first << ":";
            int check = 0;
            int iteration = pair.second.size();
            for(auto const& elem : pair.second) {
                if(pair.second.size() == 1) {
                    cout << "R" << elem;
                } else if (check < iteration-1) {
                    cout << "R" << elem << ",";
                    check++;
                } else {
                    cout << "R" << elem;
                }
            }
            cout << "\n";
        }
        cout << endl;

    }//end of SetDependencyGraph

    void SetReversedGraph(vector <Rule*> rules){

        //TODO SET UP THE KEY OF THE MAP WITH ALL THE RULES
        keyNumber = 0;
        for (auto &j: rules) {
            reversedGraph[keyNumber];
            keyNumber++;
            j->GetHeadPredicate();
        }

        //TODO SET UP THE VALUE(S) FOR EACH KEY --> DEPENDENCY
        valueForKeyNumber = 0;
        int indexRule = 0;
        for (auto &i: rules) {
            vector<Predicate *> bodyPredicate = i->GetBodyPredicate();
            for (auto &j : bodyPredicate){
                for(auto &k : rules){
                    if(j->GetName() == k->GetHeadPredicate()->GetName()) {
                        auto itr = reversedGraph.find(valueForKeyNumber);
                        itr->second.insert(indexRule);
                    }
                    valueForKeyNumber++;
                }
                valueForKeyNumber = 0;
            }
            indexRule++;
        }

        //TODO TEST CASE
/*        cout << "Reversed Graph " << endl;
        for(auto const& pair : reversedGraph) {
            cout << pair.first << ": ";
            for(auto const& elem : pair.second) {
                cout << elem << ", ";
            }
            cout << "\n";
        }*/

    }

    int CreatePostOrder(vector<Rule*> rules) {

    for(auto it=reversedGraph.begin();it!=reversedGraph.end();++it){  //Loop to iterate over map elements
        bool dependencyFound = false;
        bool addedDependentValue = false;
        if(!NodeVisited(it->first)) {
            // add the value to the theStack
            theStack.push(it->first);

            // check the dependents values
            for(auto it1=it->second.begin(); it1 !=it->second.end(); it1++) {
                while(it1 != it->second.end()) {
                    if(!NodeVisited(*it1)) {
                        // add the value to the theStack
                        theStack.push((*it1));

                        // look at that new rule
                        CreatePostOrder(*it1, rules);
                        addedDependentValue = true;
                    } else {
                        it1++;
                    }

                    if(addedDependentValue) {
                        it1 = it->second.end();
                    }

                }


                //CREATE DFSTree
                //cout << "REACHING THE WHILE LOOP " << endl;
                //TODO POP OF THE STACK AND CREATE DFS TREE
                dependencyFound = true;
                while (!theStack.empty()){
                    postOrderVec.push_back(theStack.top());
                    //postOrderVec.push_back(theStack.top());
                    theStack.pop();
                }

                //DFSTree.push_back(v);
                //v.clear();
                break;

            }

        }

        if (!dependencyFound) {
            vector <int> v;
            while (!theStack.empty()){
                postOrderVec.push_back(theStack.top());
                theStack.pop();
            }
            v.clear();

        }
    }

    return valuesVisitedVec.size();

    } //end of CreatePosteOrder1

    bool CreatePostOrder(int nextValue, vector<Rule*> rules) {
        //TODO ITERATE THROUGH THE NEW RULE

        map<int,set<int>>::iterator it;
        it = reversedGraph.find(nextValue);

        bool endOfTree = true;
        for(auto it1=it->second.begin(); it1 !=it->second.end(); it1++) {

            if (!NodeVisited(*it1)) {
                // add the value to the theStack
                theStack.push((*it1));
                endOfTree = false;
                // look at that new rule
                CreatePostOrder(*it1, rules);
                return true;
            }
        }

        if (it->second.empty() || endOfTree){

            if(rules.size() == valuesVisitedVec.size()){
                return true;
            }

            postOrderVec.push_back(theStack.top());
            //postOrderVec.push_back(theStack.top());
            theStack.pop();
            if(!theStack.empty()) {
                CreatePostOrder(theStack.top(), rules);
            } else {
                return true;
            }
        }


        return true;

    }//end of CreatePostOrder2

    void ReversePostOrder() {

        for(unsigned int i = 0; i < postOrderVec.size(); i++){
            theStack.push(postOrderVec.at(i));
        }

        while (!theStack.empty()){
            reverseOrderVec.push_back(theStack.top());
            theStack.pop();
        }

    }//end of ReversePostOrder

    void toPrintPostOrder() {

        cout << "Post Order" << endl;
        for (unsigned int i = 0; i < postOrderVec.size(); i++){
            cout << postOrderVec.at(i) << " ";
        }

        cout << endl;

        cout << "Reverse Post Order" << endl;
        for(unsigned int i = 0; i < reverseOrderVec.size(); i++){
            cout << reverseOrderVec.at(i) << " ";
        }
    }

    void CreateSCC() {

        valuesVisitedVec.clear();

        for(unsigned int i = 0; i < reverseOrderVec.size(); i++){  //Loop to iterate over map elements
            bool dependencyFound = false;
            bool nodeVisited = true;
            if(!NodeVisited(reverseOrderVec.at(i))) {
                nodeVisited = false;
                // add the value to the theStack
                theStack.push(reverseOrderVec.at(i));

                auto it = dependencyGraph.find(reverseOrderVec.at(i));
                // check the dependents values
                for (auto it1=it->second.begin(); it1 !=it->second.end(); ) {
                    while(it1 != it->second.end()) {
                        if(!NodeVisited(*it1)) {
                            // add the value to the theStack
                            theStack.push((*it1));

                            // look at that new rule
                            CreateSCC(*it1);
                            it1++;
                        } else {
                            it1++;
                        }

                    }

                    //CREATE DFSTree
                    //cout << "REACHING THE WHILE LOOP " << endl;
                    //TODO POP OF THE STACK AND CREATE DFS TREE
                    set <int> theSet;
                    dependencyFound = true;
                    while (!theStack.empty()){
                        theSet.insert(theStack.top());
                        theStack.pop();
                    }

                    DFSTreeSCC.push_back(theSet);
                    theSet.clear();
                    break;
                }
            }

            if (!dependencyFound && !nodeVisited) {
                set<int> theSet;
                while (!theStack.empty()){
                    theSet.insert(theStack.top());
                    theStack.pop();
                }
                DFSTreeSCC.push_back(theSet);
                theSet.clear();

            }
        }

    }

    void CreateSCC(int nextValue) {
        //TODO ITERATE THROUGH THE NEW RULE

        map<int,set<int>>::iterator it;
        it = dependencyGraph.find(nextValue);

        for(auto it1=it->second.begin(); it1 !=it->second.end(); it1++) {
            if (!NodeVisited(*it1)) {
                // add the value to the theStack
                theStack.push((*it1));

                // look at that new rule
                CreateSCC(*it1);
            }
        }

    }//end of CreatePostOrder2

    bool NodeVisited(const int &valueToCheck) {

        if(valuesVisitedVec.empty()){
            valuesVisitedVec.push_back(valueToCheck);
            return false;
        }

        //TODO DEBUG HERE
        for(unsigned int i = 0; i < valuesVisitedVec.size(); i++){
            if(valuesVisitedVec.at(i) == valueToCheck){
                return true;
            }
        }

        valuesVisitedVec.push_back(valueToCheck);
        return false;

    }

    set<int> GetSCC() {

        set<int> buff;
        buff.clear();
        buff = DFSTreeSCC.at(0);
        DFSTreeSCC.erase(DFSTreeSCC.begin()+0);
        return buff;

            /*for (auto x : DFSTreeSCC[i])
                cout << x << " ";
            cout << endl;*/

    }

    int GetSCCSize() {

        return DFSTreeSCC.size();
    }



};

