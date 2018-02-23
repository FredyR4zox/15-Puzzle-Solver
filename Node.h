/*Node Libraries for the 15-Puzzle
It contains a configuration that is the board, a parent node,
a char that is the movement that originated the board (Config and all the parents),
a depth to retain how many moves we needed to do to reach the configuration
and a pathCost to ....................*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Config.h"

using namespace std;

class Node{

private:
    Config cfg;
    Node *parent;
    char move;  //Start: 'a'; Up: 'u'; Down: 'd'; Left: 'l'; Right: 'r'
    unsigned int depth;
    unsigned int pathCost;

public:
    Node();
    Node(const vector<int> &vec);
    Node(const Config &cfg_);
    Node(Node *node, const char &move);

    Config getConfig() const;
    char getMove() const;
    Node* getParent() const;
    unsigned int getDepth() const;
    unsigned int getPathCost() const;

    void display();
    vector<Node> makeDescendants();
    string makePath();
};

//Constructor for the Node class (for args: void, vector<int> , Config and (Node,char))
Node::Node(){
    cfg = Config();
    parent = NULL;
    move = 'a';
    depth = 0;
    pathCost = 0;
}

Node::Node(const vector<int> &vec){
    cfg = Config(vec);
    parent = NULL;
    move = 'a';
    depth = 0;
    pathCost = 0;
}

Node::Node(const Config &cfg_){
    cfg = cfg_;
    parent = NULL;
    move = 'a';
    depth = 0;
    pathCost = 0;
}

Node::Node(Node *node, const char &mv){
    cfg = node->getConfig();
    cfg.move(mv);
    parent = node; // (Node *) porque sem isso ele reclama que node é const
    move = mv;
    depth = node->getDepth() + 1;
    pathCost = node->getPathCost() + 1;
}

//Getters
Config Node::getConfig() const{
    return cfg;
}

char Node::getMove() const{
    return move;
}

Node* Node::getParent() const{
    return parent;
}

unsigned int Node::getDepth() const{
    return depth;
}

unsigned int Node::getPathCost() const{
    return pathCost;
}

//Print the board on stdout
void Node::display(){
    cfg.display();
}

//Make the descendants of the current node
//i.e.: move up, down, left and right
//It will generate 4 Nodes at max (node not on limit of rows or columns)
//And 2 min (Node in corner)
vector<Node> Node::makeDescendants(){
    vector<char> moves = cfg.possibleMoves();
    vector<Node> l;

    for(unsigned int i=0; i<moves.size(); i++){
        Node node = Node(this, moves.at(i));
        l.push_back(node);
    }

    return l;
}

//When the solution is found, print what moves were made
string Node::makePath(){
    string path = "";
    path += move;
    Node *node = parent;
    cout << this << endl;

    cout << "make" << endl;

    while(node != NULL){
        cout << node << endl;
        char c = node->getMove();
        path+= string(" >- ") + c;
        node = node->getParent();
    }

    return string(path.rbegin(), path.rend());  //reverse the string
}