#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "Config.h"

using namespace std;

/*Bibliotecas de Nós/Nodes (e movimento) para Jogo dos 15*/

//Classe de Nós
/*Os membros de dados são a configuração do tabuleiro, um apontador para o Nó pai,
o movimento que originou este nó, a profundidade do nó, o custo do caminho 
originado e uma fila de nós filhos.*/
class Node{

private:
    Config cfg;
    Node *parent;
    Move last;
    unsigned int depth;
    unsigned int path_cost;

public:
    Node();
    Node(const vector<int> &vec);
    Node(const Config &cfg_);
    Node(Node *node, const Move &move);
    Config getConfig() const;
    Move getMove() const;
    Node* getParent() const;
    unsigned int getDepth() const;
    unsigned int getPathCost() const;
    vector<Node> makeDescendants();
    string makePath();
    void display();
};

//Métodos para a classe de Nós
//Construtores de Nós para void e int[]
Node::Node(){
    cfg = Config();
    parent = NULL;
    last = Move();
    depth = 0;
    path_cost = 0;
}

Node::Node(const vector<int> &vec){
    cfg = Config(vec);
    parent = NULL;
    last = Move();
    depth = 0;
    path_cost = 0;
}

Node::Node(const Config &cfg_){
    cfg = cfg_;
    parent = NULL;
    last = Move();
    depth = 0;
    path_cost = 0;
}

Node::Node(Node *node, const Move &mv){
    cfg = node->getConfig();
    cfg.move(mv);
    parent = node; // (Node *) porque sem isso ele reclama que node é const
    last = mv;
    depth = node->getDepth() + 1;
    path_cost = node->getPathCost() + 1;

    cout << "Build: " << this << "   parent: " << parent << endl;
}

//"Getter" para obter a matriz da configuração (que é privada) e não pode ser acedida a partir desta classe.
void Node::display(){
    cfg.display();
}

Config Node::getConfig() const{
    return cfg;
}

Move Node::getMove() const{
    return last;
}

Node* Node::getParent() const{
    return parent;
}

unsigned int Node::getDepth() const{
    return depth;
}

unsigned int Node::getPathCost() const{
    return path_cost;
}

vector<Node> Node::makeDescendants(){
    vector<char> moves = cfg.possibleMoves();
    vector<Node> l;
    
    for(unsigned int i=0; i<moves.size(); i++){
        Node node = Node(this, Move(moves[i]));
        l.push_back(node);
    }

    return l;
}

string Node::makePath(){
    string path = "";
    Node *node = this;

    while(node != NULL){
        char c = node->getMove().getMove();
        path+=c;
        node = node->getParent();
    }

    return path;
}

//tirar a biblioteca Move.h?