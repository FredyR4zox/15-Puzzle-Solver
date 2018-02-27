/*Search Functions for the 15-Puzzle*/

#include <iostream>
#include <array>
#include <queue>
#include <stack>
#include <limits>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_set>

#include "Heuristics.h"

using namespace std;

//Prototype declarations
unsigned int inversions(Config &initialConfig);
bool solutionExists(Config &initialConfig, Config &finalConfig);

string GENERAL_SEARCH_DFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth, unsigned int& generatedNodes);
string GENERAL_SEARCH_BFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth, unsigned int& generatedNodes);
string GENERAL_SEARCH_GREEDY(Config &initialConfig, Config &finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag, unsigned int& generatedNodes);
string GENERAL_SEARCH_ASTAR(Config &initialConfig, Config &finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag, unsigned int& generatedNodes);

string DFS(Config &initialConfig, Config &finalConfig);
string LDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth);
string IDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth);
string BFS(Config &initialConfig, Config &finalConfig);
string ASTAR(Config &initialConfig, Config &finalConfig, unsigned int heuristicsFlag);
string GREEDY(Config &initialConfig, Config &finalConfig, unsigned int heuristicsFlag);
//Function to check if we can reach a solution from the initial configuration
unsigned int inversions(Config &initialConfig){
    unsigned int n=0;

    array< array<int, 4>, 4> matrix = initialConfig.getMatrix();

    array<int, 16> arr;
    for(unsigned int i=0; i < 4; i++){
        for(unsigned int j=0; j < 4; j++)
            arr[i*4 + j] = matrix[i][j];
    }

    for(unsigned int i=0; i < 16; i++){
        n += arr[i];
        for(unsigned int j=0; j <= i; j++){
            if(arr[i] >= arr[j] && arr[i]!=0 && arr[j]!=0)
                n--;
        }
    }

    return n;
}

bool solutionExists(Config &initialConfig, Config &finalConfig){
    return ((inversions(initialConfig)%2 == 0) == (abs((int)initialConfig.getEmptyRowIndex()-4)%2 == 1)) == 
            ((inversions(finalConfig)%2 == 0) == (abs((int)finalConfig.getEmptyRowIndex()-4)%2 == 1));
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH_DFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth, unsigned int& generatedNodes){
    Node *initialNode = new Node(initialConfig);
    Node *solution = new Node(finalConfig);

    generatedNodes+=2;

    if(!solutionExists(initialConfig, finalConfig)){
        delete initialNode;
        delete solution;
        return "Solution not found";    //There is no solution
    }

    stack<Node*> q;  //Double-Ended QUEue to be able to insert in the front or the back, depending on the pos (or function iterator)
    q.push(initialNode);

    unordered_set<Config> hashSet;

    while(!q.empty()){
        Node *removed = q.top();
        q.pop();

        if(removed->getConfig() == solution->getConfig()){
            string str = removed->makePath();
            delete initialNode;
            delete solution;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(hashSet);
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;
    delete solution;

    return "Solution not found";
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH_BFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth,unsigned int& generatedNodes){
    Node *initialNode = new Node(initialConfig);
    Node *solution = new Node(finalConfig);

    generatedNodes+=2;

    if(!solutionExists(initialConfig, finalConfig)){
        delete initialNode;
        delete solution;
        return "Solution not found";    //There is no solution
    }

    queue<Node*> q;
    q.push(initialNode);

    unordered_set<Config> hashSet;

    unsigned depth = 0;

    while(!q.empty()){
        Node *removed = q.front();
        q.pop();

        if(removed->getDepth() > depth){
            cout << "Altura: " << removed->getDepth() << "\tNós gerados: " << generatedNodes << endl;
            depth = removed->getDepth();
        }

        if(removed->getConfig() == solution->getConfig()){
            string str = removed->makePath();
            delete initialNode;
            delete solution;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(hashSet);
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;
    delete solution;

    return "Solution not found";
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH_ASTAR(Config &initialConfig, Config &finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag, unsigned int& generatedNodes){
    Node *initialNode = new Node(initialConfig);
    Node *solution = new Node(finalConfig);

    generatedNodes+=2;

    if(!solutionExists(initialConfig, finalConfig)){
        delete initialNode;
        delete solution;
        return "Solution not found";    //There is no solution
    }

    priority_queue<Node*, vector<Node*>, compareNodes> q;
    q.push(initialNode);

    unordered_set<Config> hashSet;

    while(!q.empty()){
        Node *removed = q.top();
        q.pop();

        if(removed->getConfig() == solution->getConfig()){
            string str = removed->makePath();
            delete initialNode;
            delete solution;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(hashSet);
            calcPathCostASTAR(descendantList, finalConfig, heuristicsFlag); //calculates the pathCost for each of the children Nodes
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;
    delete solution;

    return "Solution not found";
}


//General Search Algorithm to search for a solution
string GENERAL_SEARCH_GREEDY(Config &initialConfig, Config &finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag, unsigned int& generatedNodes){
    Node *initialNode = new Node(initialConfig);
    Node *solution = new Node(finalConfig);

    generatedNodes+=2;

    if(!solutionExists(initialConfig, finalConfig)){
        delete initialNode;
        delete solution;
        return "Solution not found";    //There is no solution
    }

    priority_queue<Node*, vector<Node*>, compareNodes> q;
    q.push(initialNode);

    unordered_set<Config> hashSet;

    while(!q.empty()){
        Node *removed = q.top();
        q.pop();

        if(removed->getConfig() == solution->getConfig()){
            string str = removed->makePath();
            delete initialNode;
            delete solution;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(hashSet);
            calcPathCostGREEDY(descendantList, finalConfig,heuristicsFlag); //calculates the pathCost for each of the children Nodes
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;
    delete solution;

    return "Solution not found";
}


string DFS(Config &initialConfig, Config &finalConfig){ /*Depth first search function*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH_DFS(initialConfig, finalConfig, 80, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}

string LDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){ /*Limited Breadth first search function*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH_DFS(initialConfig, finalConfig, maxDepth, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}

string IDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){  /*Iterative Depth first search function*/
    for(unsigned int i=1; i<=maxDepth; i++){
        unsigned int generatedNodes = 0;
        string str = GENERAL_SEARCH_DFS(initialConfig, finalConfig, i, generatedNodes);
        cout << "Altura: " << i << "   \tNós gerados: " << generatedNodes << endl;
        if(str != "Solution not found")
            return str;
    }

    return "Solution not found";
}

string BFS(Config &initialConfig, Config &finalConfig){ /*Breadth first search function*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH_BFS(initialConfig, finalConfig, 80, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}
string ASTAR(Config &initialConfig, Config &finalConfig, unsigned int heuristicsFlag){   /*A* search function calls overloaded 2nd version of BFS*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH_ASTAR(initialConfig, finalConfig, 80, heuristicsFlag, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}

string GREEDY(Config &initialConfig, Config &finalConfig, unsigned int heuristicsFlag){    /*Greedy with Heuristics search function*/
    unsigned int generatedNodes = 0;
    string str = GENERAL_SEARCH_GREEDY(initialConfig, finalConfig, 80, heuristicsFlag, generatedNodes);
    cout << "Nós gerados: " << generatedNodes << endl;
    return str;
}