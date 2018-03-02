/*Search Functions for the 15-Puzzle*/

#include <iostream>
#include <array>
#include <queue>
#include <stack>
#include <unordered_set>

#include "Heuristics.h"

using namespace std;

//Change value to change the maximum depth of DFS, BFS, ASTAR and GREEDY
#define MAX_DEPTH 80

//Global function declarations
unsigned int generatedNodes;
unsigned int visitedNodes;


//Prototype declarations
unsigned int inversions(Config& initialConfig);
bool solutionExists(Config& initialConfig, Config& finalConfig);

string GENERAL_SEARCH_DFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth);
string GENERAL_SEARCH_LDFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth);
string GENERAL_SEARCH_BFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth);
string GENERAL_SEARCH_GREEDY(Config& initialConfig, Config& finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag);
string GENERAL_SEARCH_ASTAR(Config& initialConfig, Config& finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag);

void DFS(Config& initialConfig, Config& finalConfig);
void LDFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth);
void IDFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth);
void BFS(Config& initialConfig, Config& finalConfig);
void ASTAR(Config& initialConfig, Config& finalConfig, unsigned int heuristicsFlag);
void GREEDY(Config& initialConfig, Config& finalConfig, unsigned int heuristicsFlag);

//Function to check if we can reach a solution from the initial configuration
unsigned int inversions(Config& initialConfig){
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

bool solutionExists(Config& initialConfig, Config& finalConfig){
    return ((inversions(initialConfig)%2 == 0) == (abs((int)initialConfig.getEmptyRowIndex()-4)%2 == 1)) == 
            ((inversions(finalConfig)%2 == 0) == (abs((int)finalConfig.getEmptyRowIndex()-4)%2 == 1));
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH_DFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth){
    Node *initialNode = new Node(initialConfig);
    generatedNodes++;

    stack<Node*> q;
    q.push(initialNode);

    unordered_set<Config> hashSet;

    while(!q.empty()){
        Node *removed = q.top();
        q.pop();

        visitedNodes++;

        if(removed->getConfig() == finalConfig){
            cout << "Solução encontrada na profundidade: " << removed->getDepth() << endl;
            string str = removed->makePath();
            delete initialNode;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(&hashSet);
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;

    return "Solution not found";
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH_LDFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth){
    Node *initialNode = new Node(initialConfig);
    generatedNodes++;

    stack<Node*> q;
    q.push(initialNode);

    while(!q.empty()){
        Node *removed = q.top();
        q.pop();

        visitedNodes++;

        if(removed->getConfig() == finalConfig){
            cout << "Solução encontrada na profundidade: " << removed->getDepth() << endl;
            string str = removed->makePath();
            delete initialNode;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(NULL);
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;

    return "Solution not found";
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH_BFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth){
    Node *initialNode = new Node(initialConfig);
    generatedNodes++;

    queue<Node*> q;
    q.push(initialNode);

    unordered_set<Config> hashSet;

    unsigned int depth = 0;

    while(!q.empty()){
        Node *removed = q.front();
        q.pop();

        if(removed->getDepth() > depth){
            cout << "Altura: " << removed->getDepth() << "\tTotal de nós gerados: " << generatedNodes << " \tTotal de nós visitados: " << visitedNodes << endl;
            depth = removed->getDepth();
        }

        visitedNodes++;

        if(removed->getConfig() == finalConfig){
            cout << endl << "Solução encontrada na profundidade: " << removed->getDepth() << endl;
            string str = removed->makePath();
            delete initialNode;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(&hashSet);
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;

    return "Solution not found";
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH_ASTAR(Config& initialConfig, Config& finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag){
    Node *initialNode = new Node(initialConfig);
    generatedNodes++;

    priority_queue<Node*, vector<Node*>, compareNodes> q;
    q.push(initialNode);

    while(!q.empty()){
        Node *removed = q.top();
        q.pop();

        visitedNodes++;

        if(removed->getConfig() == finalConfig){
            cout << "Solução encontrada na profundidade: " << removed->getDepth() << endl;
            string str = removed->makePath();
            delete initialNode;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(NULL);
            calcPathCostASTAR(descendantList, finalConfig, heuristicsFlag); //calculates the pathCost for each of the children Nodes
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;

    return "Solution not found";
}


//General Search Algorithm to search for a solution
string GENERAL_SEARCH_GREEDY(Config& initialConfig, Config& finalConfig, unsigned int maxDepth, unsigned int heuristicsFlag){
    Node *initialNode = new Node(initialConfig);
    generatedNodes++;

    priority_queue<Node*, vector<Node*>, compareNodes> q;
    q.push(initialNode);

    unordered_set<Config> hashSet;

    while(!q.empty()){
        Node *removed = q.top();
        q.pop();

        visitedNodes++;

        if(removed->getConfig() == finalConfig){
            cout << "Solução encontrada na profundidade: " << removed->getDepth() << endl;
            string str = removed->makePath();
            delete initialNode;
            return str;
        }

        if(removed->getDepth() < maxDepth){
            array<Node*, 4> descendantList = removed->makeDescendants(&hashSet);
            calcPathCostGREEDY(descendantList, finalConfig,heuristicsFlag); //calculates the pathCost for each of the children Nodes
            for(unsigned int i=0; i<4 && descendantList[i]!=NULL; i++){
                generatedNodes++;
                q.push(descendantList[i]);
            }
        }
    }

    delete initialNode;

    return "Solution not found";
}


void DFS(Config& initialConfig, Config& finalConfig){   /*Depth first search function*/
    if(!solutionExists(initialConfig, finalConfig)){
        cout << "Não é possivel chegar à configuração final a partir da configuração inicial" << endl << endl;    //There is no solution
        return;
    }

    generatedNodes = visitedNodes = 0;
    string str = GENERAL_SEARCH_DFS(initialConfig, finalConfig, MAX_DEPTH);
    
    if(str != "Solution not found")
        cout << "Movimentos: " << str << endl << endl;
    else
        cout << "Solução não encontrada" << endl << endl;
    
    cout << "Nós gerados: " << generatedNodes << endl;
    cout << "Nós visitados: " << visitedNodes << endl;
    cout << "Máximo de memória gasta em nós: " << (generatedNodes*sizeof(Node))/1024 << " KB" << endl << endl;
}

void LDFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth){ /*Limited Breadth first search function*/
    if(!solutionExists(initialConfig, finalConfig)){
        cout << "Não é possivel chegar à configuração final a partir da configuração inicial" << endl << endl;    //There is no solution
        return;
    }

    generatedNodes = visitedNodes = 0;
    string str = GENERAL_SEARCH_LDFS(initialConfig, finalConfig, maxDepth);
    
    if(str != "Solution not found")
        cout << "Movimentos: " << str << endl << endl;
    else
        cout << "Solução não encontrada" << endl << endl;
    
    cout << "Nós gerados: " << generatedNodes << endl;
    cout << "Nós visitados: " << visitedNodes << endl;
    cout << "Máximo de memória gasta em nós: " << (generatedNodes*sizeof(Node))/1024 << " KB" << endl << endl;
}

void IDFS(Config& initialConfig, Config& finalConfig, unsigned int maxDepth){  /*Iterative Depth first search function*/
    if(!solutionExists(initialConfig, finalConfig)){
        cout << "Não é possivel chegar à configuração final a partir da configuração inicial" << endl << endl;    //There is no solution
        return;
    }

    for(unsigned int i=1; i<=maxDepth; i++){
        generatedNodes = visitedNodes = 0;
        string str = GENERAL_SEARCH_LDFS(initialConfig, finalConfig, i);
        
        cout << "Altura: " << i << "\tNós gerados: " << generatedNodes << "  \tNós visitados: " << visitedNodes << endl;
        cout << "Máximo de memória gasta em nós: " << (generatedNodes*sizeof(Node))/1024 << " KB" << endl << endl;
        
        if(str != "Solution not found"){
            cout << "Movimentos: " << str << endl <<  endl;
            return;
        }
    }

    cout << "Solução não encontrada" << endl << endl;
}

void BFS(Config& initialConfig, Config& finalConfig){ /*Breadth first search function*/
    if(!solutionExists(initialConfig, finalConfig)){
        cout << "Não é possivel chegar à configuração final a partir da configuração inicial" << endl << endl;    //There is no solution
        return;
    }

    generatedNodes = visitedNodes = 0;
    string str = GENERAL_SEARCH_BFS(initialConfig, finalConfig, MAX_DEPTH);
    
    if(str != "Solution not found")
        cout << "Movimentos: " << str << endl << endl;
    else
        cout << "Solução não encontrada" << endl << endl;
    
    cout << "Nós gerados: " << generatedNodes << endl;
    cout << "Nós visitados: " << visitedNodes << endl;
    cout << "Máximo de memória gasta em nós: " << (generatedNodes*sizeof(Node))/1024 << " KB" << endl << endl;
}

void ASTAR(Config& initialConfig, Config& finalConfig, unsigned int heuristicsFlag){   /*A* search function calls overloaded 2nd version of BFS*/
    if(!solutionExists(initialConfig, finalConfig)){
        cout << "Não é possivel chegar à configuração final a partir da configuração inicial" << endl << endl;    //There is no solution
        return;
    }

    generatedNodes = visitedNodes = 0;
    string str = GENERAL_SEARCH_ASTAR(initialConfig, finalConfig, MAX_DEPTH, heuristicsFlag);
    
    if(str != "Solution not found")
        cout << "Movimentos: " << str << endl << endl;
    else
        cout << "Solução não encontrada" << endl << endl;
    
    cout << "Nós gerados: " << generatedNodes << endl;
    cout << "Nós visitados: " << visitedNodes << endl;
    cout << "Máximo de memória gasta em nós: " << (generatedNodes*sizeof(Node))/1024 << " KB" << endl << endl;
}

void GREEDY(Config& initialConfig, Config& finalConfig, unsigned int heuristicsFlag){    /*Greedy with Heuristics search function*/
    if(!solutionExists(initialConfig, finalConfig)){
        cout << "Não é possivel chegar à configuração final a partir da configuração inicial" << endl << endl;    //There is no solution
        return;
    }
    
    generatedNodes = visitedNodes = 0;
    string str = GENERAL_SEARCH_GREEDY(initialConfig, finalConfig, MAX_DEPTH, heuristicsFlag);
    
    if(str != "Solution not found")
        cout << "Movimentos: " << str << endl << endl;
    else
        cout << "Solução não encontrada" << endl << endl;
    
    cout << "Nós gerados: " << generatedNodes << endl;
    cout << "Nós visitados: " << visitedNodes << endl;
    cout << "Máximo de memória gasta em nós: " << (generatedNodes*sizeof(Node))/1024 << " KB" << endl << endl;
}