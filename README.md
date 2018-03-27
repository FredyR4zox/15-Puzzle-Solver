# IA-Project-1
First project of Artificial Inteligence, which consisted in developing a bot to solve the 15-puzzle using heuristic search.
Our implementation was in C++.


### Search functions implemented
* DFS - Depth First Search
* LDFS - Limited Depth First Search
* IDFS - Iteractive Depth First Search
* BFS - Breadth First Search
* A* - A Star Search
* Greedy - Greedy Search


### Compilation
``` bash
$ g++ -O3 main.cpp -o main
```

### Usage
The usage of this project is intuitive. It's instructions appear when the program is executed.


### Files
* main.cpp - Requests input and calls the search functions
* Node.h - Implementation of the graph node's
* Config.h 	- Implementation of the game board and functions to work with the board
* SearchMethods.h - Search functions to search for the steps to take to the solution
* Heuristics.h - Functions to calculate the cost of the Node's
* test's - Initial and final configurations of boards to test the program
