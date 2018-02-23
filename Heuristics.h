/*Heuristics Header*/

/*In the IA Book, it refers that the 15-puzzle problem can be solved using heuristics in the following manner:
h(n) = h1(n) or h2(n) where h1(n) is the number of misplaced tiles and h2(n) the Manhattan distance*/

#include <vector>
#include <cmath>
#include "Node.h"
using namespace std;


class Heuristics {
	private:

	public:
	int calcH1(Node actual, Config goal);
	int calcH2(Node actual, Config goal);
	vector<int> getColRowFinal(Config goal, int value);

};

//Number of misplaced tiles
int Heuristics::calcH1(Node actual, Config goal) {
	int misplaced = 0;
	for (int i = 0 ; i < 4 ; i++)
		for (int j = 0 ; j < 4 ; j++)
			if (actual.getConfig().getMatrix().at(i).at(j) != goal.getMatrix().at(i).at(j))
				misplaced++;
	return misplaced;
}

//Manhattan Distance (or the sum of the distances of the tiles from their goal positions)
int Heuristics::calcH2(Node actual, Config goal) {
	int count = 0;
	int place = 0;
	for (int i = 0 ; i < actual.getConfig().getMatrix().size() ; i++) { //rows
		for (int j = 0 ; j < actual.getConfig().getMatrix().at(i).size() ; j++) /*cols*/ {
			int value = actual.getConfig().getMatrix().at(i).at(j);
			vector<int> final = getColRowFinal(goal, value); //Obtains the Column and Row of the correct spot for the tile [0]:row ; [1]: col
			place++;
			if (value != 0 && value != place) {
				count += abs(i - final.at(0)) + abs(j - final.at(1));
			}
		}
	}
	return count;
}

//Gets the position of the column and row on their correct place
vector<int> Heuristics::getColRowFinal(Config goal, int value) {
	vector<int> final;
	for (int i = 0; i < goal.getMatrix().size() ; i++)
		for (int j = 0; j < goal.getMatrix().at(i).size(); j++)
			if (goal.getMatrix().at(i).at(j) == value)
			{
				final.push_back(i);
				final.push_back(j);
				return final;
			}
}
