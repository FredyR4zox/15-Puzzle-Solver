/*Node Libraries for the 15-Puzzle
It contains a configuration that is the board, a parent node,
a char that is the movement that originated the board (Config and all the parents),
a depth to retain how many moves we needed to do to reach the configuration
and a pathCost to ....................*/

#include <iostream>
#include <array>
#include <unordered_set>

#include "Config.h"

using namespace std;

class Node{
    friend inline bool operator<(const Node& left, const Node& right);
    friend inline bool operator>(const Node& left, const Node& right);

private:
    Config cfg;
    Node *parent;
    char move;  //Start: 's'; Up: 'u'; Down: 'd'; Left: 'l'; Right: 'r'
    unsigned int depth;
    unsigned int pathCost;
    array<Node*, 4> children;

public:
    Node();
    Node(const array<int, 16>& arr);
    Node(const Config& cfg_);
    Node(Node& node, const char& move);
    ~Node();

    void setPathCost(const unsigned int cost);

    inline Config getConfig() const;
    inline Node* getParent() const;
    inline char getMove() const;
    inline unsigned int getDepth() const;
    inline unsigned int getPathCost() const;
    inline array<Node*, 4> getChildren() const;

    void display();
    array<Node*, 4> makeDescendants(unordered_set<Config>* hashSet);
    string makePath();
};



//Constructor for the Node class (for args: void, vector<int> , Config and (Node,char))
Node::Node(){
    cfg = Config();
    parent = NULL;
    move = 's';
    depth = 0;
    pathCost = 0;
    for(unsigned int i=0; i<4; i++)
        children[i] = NULL;
}

Node::Node(const array<int, 16>& arr){
    cfg = Config(arr);
    parent = NULL;
    move = 's';
    depth = 0;
    pathCost = 0;
    for(unsigned int i=0; i<4; i++)
        children[i] = NULL;
}

Node::Node(const Config& cfg_){
    cfg = cfg_;
    parent = NULL;
    move = 's';
    depth = 0;
    pathCost = 0;
    for(unsigned int i=0; i<4; i++)
        children[i] = NULL;
}

Node::Node(Node& node, const char& mv){
    cfg = node.getConfig();
    cfg.move(mv);
    parent = &node;
    move = mv;
    depth = node.getDepth() + 1;
    pathCost = 0;
    for(unsigned int i=0; i<4; i++)
        children[i] = NULL;
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
array<Node*, 4> Node::makeDescendants(unordered_set<Config>* hashSet){
    array<char, 4> moves = cfg.possibleMoves();
    array<Node*, 4> l = {};
    unsigned int index = 0;

    for(unsigned int i=0; i<4 && moves[i]!=0; i++){
        Node *node = new Node(*this, moves[i]);
        if(hashSet != NULL){
            if(hashSet->insert(node->getConfig()).second == false){
                delete node;
                continue;
            }
        }
        for(unsigned int i=0; i<4; i++){
            if(this->children[i]==NULL){
                this->children[i] = node;
                break;
            }
        }
        l[index] = node;
        index++;
    }

    return l;
}

//When the solution is found, print what moves were made
string Node::makePath(){
    string path = "";
    Node *node = this;

    while(node != NULL){
        char c = node->getMove();
        switch(c){
            case 's':
                path += "oicinI";
                break;
            case 'u':
                path += "amic >- ";
                break;
            case 'd':
                path += "oxiab >- ";
                break;
            case 'l':
                path += "adreuqse >- ";
                break;
            case 'r':
                path += "atierid >- ";
                break;
        }
        node = node->getParent();
    }

    return string(path.rbegin(), path.rend());  //reverse the string
}



//Operator overloading for sorting using pathCost
struct compareNodes{
    bool operator()(const Node* left, const Node* right) const{
        return (left->getPathCost() > right->getPathCost());
    }
};

inline bool operator<(const Node& left, const Node& right){
    return (left.pathCost < right.pathCost);
}

inline bool operator>(const Node& left, const Node& right){
    return (left.pathCost > right.pathCost);
}


//mudar Node & para Node& etc