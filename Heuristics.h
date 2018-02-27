/*Heuristics Header*/

/*In the IA Book, it refers that the 15-puzzle problem can be solved using heuristics in the following manner:
h(n) = h1(n) or h2(n) where h1(n) is the number of misplaced tiles and h2(n) the Manhattan distance*/

#include <array>
#include <cmath>

#include "Node.h"

using namespace std;

//Prototype declarations
int calcH1(Node *actual, Config goal);
int calcH2(Node *actual, Config goal);
array<int, 2> getColRowFinal(Config goal, int value);
void calcPathCost(array<Node*, 4> v, Config goal, unsigned int heuristic);
void calcPathCostGreedy(array<Node*, 4> v, Config goal, unsigned int heuristic);


//The sum of h1+h2 is the weight of the Node. This way, A* can know what Node to expand first. Less is better.
//We can use h1 or h2 or h1+h2, let's use the sum for test purposes.

//Heuristics: h1 or h2 or (h1+h2)
//case 0: Heuristic 1 ; case 1: Heuristic 2 ; case 2: Heuristic 1 + Heuristic 2
void calcPathCostASTAR(array<Node*, 4> v, Config goal,unsigned int heuristic){
    switch (heuristic) {
        case 0:  
                for(unsigned int i = 0; i<4 && v[i]!=NULL ; i++){
                    v[i]->setPathCost(v[i]->getDepth() + calcH1(v[i], goal));}
                break;
        case 1:
                for(unsigned int i = 0; i<4 && v[i]!=NULL ; i++){
                    v[i]->setPathCost(v[i]->getDepth() + calcH2(v[i], goal));}
                break;
        case 2:
                for(unsigned int i = 0; i<4 && v[i]!=NULL ; i++){
                    v[i]->setPathCost(v[i]->getDepth() + calcH1(v[i], goal) + calcH2(v[i],goal));}
                break;
    }
}

void calcPathCostGreedy(array<Node*, 4> v, Config goal,unsigned int heuristic){
    switch (heuristic) {
        case 0:  
                for(unsigned int i = 0; i<4 && v[i]!=NULL ; i++){
                    v[i]->setPathCost(calcH1(v[i], goal));}
                break;
        case 1:
                for(unsigned int i = 0; i<4 && v[i]!=NULL ; i++){
                    v[i]->setPathCost(calcH2(v[i], goal));}
                break;
        case 2:
                for(unsigned int i = 0; i<4 && v[i]!=NULL ; i++){
                    v[i]->setPathCost(calcH1(v[i], goal) + calcH2(v[i],goal));}
                break;
    }
}

//Heuristic 1: Number of misplaced tiles
int calcH1(Node *actual, Config goal){
    int misplaced = 0;
    for(unsigned int i = 0 ; i < 4 ; i++){
        for(unsigned int j = 0 ; j < 4 ; j++){
            if(actual->getConfig().getMatrix()[i][j] != goal.getMatrix()[i][j])
                misplaced++;
        }
    }
    
    return misplaced;
}

//Heuristic 2: Manhattan Distance (or the sum of the distances of the tiles from their goal positions)
int calcH2(Node *actual, Config goal){
    int count = 0;
    int place = 0;
    for(unsigned int i = 0 ; i < 4 ; i++){   //rows
        for(unsigned int j = 0 ; j < 4 ; j++){ /*cols*/
            int value = actual->getConfig().getMatrix()[i][j];
            array<int, 2> final = getColRowFinal(goal, value);    //Obtains the Column and Row of the correct spot for the tile [0]:row ; [1]: col
            place++;
            if(value != 0 && value != place)
                count += abs((int)i - final[0]) + abs((int)j - final[1]);
        }
    }
    return count;
}

//Auxiliary function to heuristic 2: Gets the position of the column and row on their correct place
array<int, 2> getColRowFinal(Config goal, int value){
    array<int, 2> final;
    for(unsigned int i = 0; i < 4 ; i++){
        for(unsigned int j = 0; j < 4; j++){
            if(goal.getMatrix()[i][j] == value){
                final[0] = i;
                final[1] = j;
                return final;
            }
        }
    }
    return final;
}