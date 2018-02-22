#include <vector>
#include <list>
#include <queue>
#include <string>

#include "Node.h"

using namespace std;

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

int main(){
    vector<int> vec;

    for(int i=1; i<16; i++)
        vec.push_back(i);
    vec.push_back(0);

    vector<int> vec2;

    for(int i=1; i<16; i++)
        vec2.push_back(i);
    vec2.push_back(0);
    vec2[15] = 12;
    vec2[11] = 0;


    Node node = Node(vec);
    node.display();

    Node node2 = Node(vec2);
    node2.display();

    Config initialConfig = Config(vec2);
    Config finalConfig = Config(vec);

    cout << GENERAL_SEARCH(initialConfig, finalConfig, 1) << endl;

    return 0;
}