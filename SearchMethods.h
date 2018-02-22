#include <iostream>
#include <vector>
#include <deque>

#include "Node.h"

using namespace std;

/*Bibliotecas de Pesquisa para Jogo dos 15*/

bool solutionExists(Config &initialConfig, Config &finalConfig){
    return true;
}

string GENERAL_SEARCH(Config &initialConfig, Config &finalConfig, int pos){
    Node initialNode = Node(initialConfig);
    Node solution = Node(finalConfig);

    if(!solutionExists(initialConfig, finalConfig))
        return ""; //Não existe uma solução

    deque<Node> q;
    q.push_back(initialNode);

    while(!q.empty()){
        Node removed = q.front();
        q.pop_front();
        if(removed.getConfig() == solution.getConfig())
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

    return NULL;
}

void DFS(Config &initialConfig, Config &finalConfig){ /*Depth first search function*/
    cout << GENERAL_SEARCH(initialConfig, finalConfig, 0) << endl;
}

void BFS(Config &initialConfig, Config &finalConfig){ /*Breadth first search function*/
    cout << GENERAL_SEARCH(initialConfig, finalConfig, 0) << endl;
}

void IDFS() /*Iterative Depth first search function*/
{}

void Astar() /*A* search function*/
{}

void GreedyWHeuristics() /*Greedy with Heuristics search function*/
{}