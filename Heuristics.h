/*Heuristics Header*/

/*In the IA Book, it refers that the 15-puzzle problem can be solved using heuristics in the following manner:
h(n) = h1(n) or h2(n) where h1(n) is the number of misplaced tiles and h2(n) the Manhattan distance*/

#include <vector>
#include <cmath>

#include "Node.h"

using namespace std;

//Prototype declarations
int calcH1(Node *actual, Config goal);
int calcH2(Node *actual, Config goal);
vector<int> getColRowFinal(Config goal, int value);
void calcPathCost(vector<Node*> v, Config goal);


//The sum of h1+h2 is the weight of the Node. This way, A* can know what Node to expand first. Less is better.
//We can use h1 or h2 or h1+h2, let's use the sum for test purposes.

void calcPathCost(vector<Node*> v, Config goal){
    for(unsigned int i = 0; i < v.size() ; i++){
        v.at(i)->setPathCost(calcH1(v.at(i), goal) + calcH2(v.at(i), goal));
        /*Podes apagar este cout, é só para dar output dos pesos dos nós*/
        cout << "Custo do nó" << " " << i << ":" << v.at(i)->getPathCost() << endl;
    }
}

//Heuristic 1: Number of misplaced tiles
int calcH1(Node *actual, Config goal){
    int misplaced = 0;
    for(unsigned int i = 0 ; i < 4 ; i++){
        for(unsigned int j = 0 ; j < 4 ; j++){
            if(actual->getConfig().getMatrix().at(i).at(j) != goal.getMatrix().at(i).at(j))
                misplaced++;
        }
    }
    
    return misplaced;
}

//Heuristic 2: Manhattan Distance (or the sum of the distances of the tiles from their goal positions)
int calcH2(Node *actual, Config goal){
    int count = 0;
    int place = 0;
    for(unsigned int i = 0 ; i < actual->getConfig().getMatrix().size() ; i++){   //rows
        for(unsigned int j = 0 ; j < actual->getConfig().getMatrix().at(i).size() ; j++){ /*cols*/
            int value = actual->getConfig().getMatrix().at(i).at(j);
            vector<int> final = getColRowFinal(goal, value);    //Obtains the Column and Row of the correct spot for the tile [0]:row ; [1]: col
            place++;
            if(value != 0 && value != place)
                count += abs((int)i - final.at(0)) + abs((int)j - final.at(1));
        }
    }
    return count;
}

//Auxiliary function to heuristic 2: Gets the position of the column and row on their correct place
vector<int> getColRowFinal(Config goal, int value){
    vector<int> final;
    for(unsigned int i = 0; i < goal.getMatrix().size() ; i++){
        for(unsigned int j = 0; j < goal.getMatrix().at(i).size(); j++){
            if(goal.getMatrix().at(i).at(j) == value){
                final.push_back(i);
                final.push_back(j);
                return final;
            }
        }
    }
    return final;
}