/*Node Libraries for the 15-Puzzle
It contains a configuration that is the board, a parent node,
a char that is the movement that originated the board (Config and all the parents),
a depth to retain how many moves we needed to do to reach the configuration
and a pathCost to ....................*/

#include <iostream>
#include <array>
#include <string>
#include <algorithm>

#include "Config.h"

using namespace std;

class Node{
    friend inline bool operator<(const Node& left, const Node& right);
    friend inline bool operator>(const Node& left, const Node& right);

private:
    Config cfg;
    Node *parent;
    char move;  //Start: 'a'; Up: 'u'; Down: 'd'; Left: 'l'; Right: 'r'
    unsigned int depth;
    unsigned int pathCost;
    array<Node*, 4> children;

public:
    Node();
    Node(const array<int, 16>& arr);
    Node(const Config &cfg_);
    Node(Node &node, const char &move);
    ~Node();

    void setPathCost(const unsigned int cost);

    inline Config getConfig() const;
    inline Node* getParent() const;
    inline char getMove() const;
    inline unsigned int getDepth() const;
    inline unsigned int getPathCost() const;
    inline array<Node*, 4> getChildren() const;

    void display();
    array<Node*, 4> makeDescendants();
    string makePath();
};



//Constructor for the Node class (for args: void, vector<int> , Config and (Node,char))
Node::Node(){
    cfg = Config();
    parent = NULL;
    move = 'a';
    depth = 0;
    pathCost = 0;
    for(unsigned int i=0; i<4; i++)
        children[i] = NULL;
}

Node::Node(const array<int, 16>& arr){
    cfg = Config(arr);
    parent = NULL;
    move = 'a';
    depth = 0;
    pathCost = 0;
    for(unsigned int i=0; i<4; i++)
        children[i] = NULL;
}

Node::Node(const Config &cfg_){
    cfg = cfg_;
    parent = NULL;
    move = 'a';
    depth = 0;
    pathCost = 0;
    for(unsigned int i=0; i<4; i++)
        children[i] = NULL;
}

Node::Node(Node &node, const char &mv){
    cfg = node.getConfig();
    cfg.move(mv);
    parent = &node;
    move = mv;
    depth = node.getDepth() + 1;
    pathCost = node.getPathCost() + 1;

    for(unsigned int i=0; i<4; i++){
        if(children[i]==NULL){
            children[i] = this;
            break;
        }
    }
}

Node::~Node(){
    for(unsigned int i=0; i<4; i++)
        if(children[i]!=NULL)
            delete children[i];
}



void Node::setPathCost(unsigned int cost){
    pathCost = cost;
}



//Getters
inline Config Node::getConfig() const{
    return cfg;
}

inline Node* Node::getParent() const{
    return parent;
}

inline char Node::getMove() const{
    return move;
}

inline unsigned int Node::getDepth() const{
    return depth;
}

inline unsigned int Node::getPathCost() const{
    return pathCost;
}

inline array<Node*, 4> Node::getChildren() const{
    return children;
}



//Print the board on stdout
void Node::display(){
    cout << "Depth: " << depth << "\tMove: " << move << " \tParent: " << parent << endl;
    cfg.display();
}

//Make the descendants of the current node
//i.e.: move up, down, left and right
//It will generate 4 Nodes at max (node not on limit of rows or columns)
//And 2 at min (Node in corner)
array<Node*, 4> Node::makeDescendants(){
    array<char, 4> moves = cfg.possibleMoves();
    array<Node*, 4> l = {};
    unsigned int index = 0;

    for(unsigned int i=0; i<4 && moves[i]!=0; i++){
        Node *node = new Node(*this, moves[i]);
        l[index] = node;
        index++;
    }

    return l;
}

//When the solution is found, print what moves were made
string Node::makePath(){
    string path = "";
    path += move;
    Node *node = parent;

    while(node != NULL){
        char c = node->getMove();
        path+= string(" >- ") + c;
        node = node->getParent();
    }

    return string(path.rbegin(), path.rend());  //reverse the string
}



//Operator overloading for sorting using pathCost
inline bool operator<(const Node& left, const Node& right){
    return (left.pathCost < right.pathCost);
}

inline bool operator>(const Node& left, const Node& right){
    return (left.pathCost > right.pathCost);
}


//mudar Node & para Node& etc