/*Search Functions for the 15-Puzzle*/

#include <iostream>
#include <vector>
#include <deque>
#include <limits>

#include "Node.h"

using namespace std;

//Function to check if we can reach a solution from the initial configuration
bool solutionExists(Config &initialConfig, Config &finalConfig){
    //return (Inv%2 == 0) == ((initialConfig.getEmptyX+1)%2 == 1);
    return true;
}

//General Search Algorithm to search for a solution
string GENERAL_SEARCH(Config &initialConfig, Config &finalConfig, int pos, unsigned int maxDepth){
    Node initialNode = Node(initialConfig);
    Node solution = Node(finalConfig);

    if(!solutionExists(initialConfig, finalConfig))
        return "Solution not found";    //There is no solution

    deque<Node> q;  //Double-Ended QUEue to be able to insert in the front or the back, depending on the pos (or function iterator)
    q.push_back(initialNode);

    while(!q.empty()){
        Node removed = q.front();
        q.pop_front();

        cout << "Depth: " << removed.getDepth() << "   Move: " << removed.getMove() << endl;
        removed.display();
        
        if(removed.getDepth() > maxDepth)
            break;
        else if(removed.getConfig() == solution.getConfig())
            return removed.makePath();

        vector<Node> descendantList = removed.makeDescendants();

// Se pos for 0, entao a funcao de inserir na fila vai inserir os elementos no inicio da fila
// Se pos for 1, entao a funcao de inserir na fila vai inserir os elementos no fim da fila

//em vez de pos meter um iterator
//adicionamos ao elemento q essa função para poder fazer q.begin() etc

        if(pos == 0)
            q.insert(q.begin(), descendantList.begin(), descendantList.end());
        else
            q.insert(q.end(), descendantList.begin(), descendantList.end());
    }

    return "Solution not found";
}

string DFS(Config &initialConfig, Config &finalConfig){ /*Depth first search function*/
    return GENERAL_SEARCH(initialConfig, finalConfig, 0, numeric_limits<unsigned>::max());
}

string BFS(Config &initialConfig, Config &finalConfig){ /*Breadth first search function*/
    return GENERAL_SEARCH(initialConfig, finalConfig, 1, numeric_limits<unsigned>::max());
}

string LDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){ /*Limited Breadth first search function*/
    return GENERAL_SEARCH(initialConfig, finalConfig, 0, maxDepth);
}

string IDFS(Config &initialConfig, Config &finalConfig, unsigned int maxDepth){  /*Iterative Depth first search function*/
    for(unsigned int i=0; i<maxDepth; i++){
        string str = GENERAL_SEARCH(initialConfig, finalConfig, 0, i);
        if(str != "Solution not found")
            return str;
    }

    return "Solution not found";
}

void Astar() /*A* search function*/
{}

void GreedyWithHeuristics() /*Greedy with Heuristics search function*/
{}