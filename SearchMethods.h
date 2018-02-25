/*Search Functions for the 15-Puzzle*/

#include <iostream>
#include <vector>
#include <deque>
#include <limits>
#include <string>
#include <cmath>
#include <algorithm>

#include "Heuristics.h"

using namespace std;


//Prototype declarations
unsigned int inversions(Config &initialConfig);
bool solutionExists(Config &initialConfig, Config &finalConfig);
string GENERAL_SEARCH(Config &initialConfig, Config &finalConfig, int pos, unsigned int maxDepth);
string DFS(Config &initialConfig, Config &finalConfig);
string BFS(Config &initialConfig, Config &finalConfig);
string BFS(Config &initialConfig, Config &finalConfig, int i);
string LDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth);
string IDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth);
string ASTAR(Config &initialConfig, Config &finalConfig);
void GreedyWithHeuristics();

//Function to check if we can reach a solution from the initial configuration
unsigned int inversions(Config &initialConfig){
    unsigned int n=0;

    vector< vector<int> > matrix = initialConfig.getMatrix();

    vector<int> vec;
    for(unsigned int i=0; i < 4; i++){
        for(unsigned int j=0; j < 4; j++)
            vec.push_back(matrix.at(i).at(j));
    }

    for(unsigned int i=0; i < 16; i++){
        n += vec.at(i);
        for(unsigned int j=0; j <= i; j++){
            if(vec.at(i) >= vec.at(j) && vec.at(i)!=0 && vec.at(j)!=0)
                n--;
        }
    }

    return n;
}

bool solutionExists(Config &initialConfig, Config &finalConfig){
    return (inversions(initialConfig)%2 == 0) == (abs((int)initialConfig.getEmptyRowIndex()-4)%2 == 1) == 
            (inversions(finalConfig)%2 == 0) == (abs((int)finalConfig.getEmptyRowIndex()-4)%2 == 1);
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH(Config &initialConfig, Config &finalConfig, int pos, unsigned int maxDepth){
    Node *initialNode = new Node(initialConfig);
    Node *solution = new Node(finalConfig);

    if(!solutionExists(initialConfig, finalConfig)){
        delete initialNode;
        delete solution;
        return "Solution not found";    //There is no solution
    }

    deque<Node*> q;  //Double-Ended QUEue to be able to insert in the front or the back, depending on the pos (or function iterator)
    q.push_back(initialNode);

    while(!q.empty()){
        Node *removed = q.front();
        q.pop_front();

        removed->display();
        
        if(removed->getDepth() > maxDepth)
            continue;
        else if(removed->getConfig() == solution->getConfig()){
            string str = removed->makePath();
            delete initialNode;
            delete solution;
            return str;
        }

        vector<Node*> descendantList = removed->makeDescendants(*initialNode);

// Se pos for 0, entao a funcao de inserir na fila vai inserir os elementos no inicio da fila
// Se pos for 1, entao a funcao de inserir na fila vai inserir os elementos no fim da fila

//em vez de pos meter um iterator
//adicionamos ao elemento q essa função para poder fazer q.begin() etc

        if(pos == 0)
            q.insert(q.begin(), descendantList.begin(), descendantList.end());
        else if (pos == 1)
            q.insert(q.end(), descendantList.begin(), descendantList.end());
        else{   //pos == 2, using A*
            calcPathCost(descendantList,solution->getConfig()); //calculates the pathCost for each of the children Nodes
            sort(descendantList.begin(),descendantList.end());  //sorts array so that the children Node with the less pathCost enters first in the queue
            q.insert(q.end(), descendantList.begin(), descendantList.end());
        }
    }

    delete initialNode;
    delete solution;

    return "Solution not found";
}

string DFS(Config &initialConfig, Config &finalConfig){ /*Depth first search function*/
    return GENERAL_SEARCH(initialConfig, finalConfig, 0, 25);
}

string BFS(Config &initialConfig, Config &finalConfig){ /*Breadth first search function*/
    return GENERAL_SEARCH(initialConfig, finalConfig, 1, 25);
}

/*BFS with Heuristics : has another argument "FLAG" : function overloading*/
string BFS(Config &initialConfig, Config &finalConfig, int i){  /*Breadth first search function*/
    return GENERAL_SEARCH(initialConfig, finalConfig, i, 25);
}

string LDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){ /*Limited Breadth first search function*/
    return GENERAL_SEARCH(initialConfig, finalConfig, 0, maxDepth);
}

string IDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){  /*Iterative Depth first search function*/
    for(unsigned int i=0; i<=maxDepth; i++){
        string str = GENERAL_SEARCH(initialConfig, finalConfig, 0, i);
        if(str != "Solution not found")
            return str;
    }

    return "Solution not found";
}
string ASTAR(Config &initialConfig, Config &finalConfig){   /*A* search function calls overloaded 2nd version of BFS*/
    return BFS(initialConfig, finalConfig, 2);
}

void GreedyWithHeuristics() /*Greedy with Heuristics search function*/
{}