#include <iostream>
#include <array>
#include <cstring>

#include "SearchMethods.h"

using namespace std;

int main(int argc, char const *argv[]){
    if(argc < 2 || (!strcmp(argv[1], "IDFS") && argc!=3) || (!strcmp(argv[1], "LDFS") && argc!=3) || (!strcmp(argv[1],"ASTAR") && argc !=3) || (!strcmp(argv[1],"GREEDY") && argc != 3) ){
        cout << "Usage: " << argv[0] << " [Search method] [Search options]" << endl;
        cout << "Search methods:" << endl;
        cout << "   DFS -> use Depth First Search;" << endl;
        cout << "   LDFS [Maximum Depth] -> use Limited Depth First Search, where maximum depth is the depth limit;" << endl;
        cout << "   IDFS [Maximum Depth] -> use Iteractive Depth First Search, where maximum depth is the depth limit;" << endl;
        cout << "   BFS -> use Breadth First Search;" << endl;
        cout << "   ASTAR [Heuristic] -> use A* Search;" << endl;
        cout << "   GREEDY [Heuristic] -> use Greedy Search;" << endl;
        cout << "Types of Heuristic (for ASTAR and GREEDY):" << endl;
        cout << "   0: Nº of pieces out of their final position;" << endl;
        cout << "   1: Manhattan Distance (Sum of the distance of all pieces from their final position);" << endl;
        cout << "   2: Sum of the two previous heuristics;" << endl;
        return 1;
    }

    array<int, 16> startVec;
    cout << "Insert the initial board: ";
    for(unsigned int i=0; i<16; i++)
        cin >> startVec[i];

    array<int, 16> finalVec;
    cout << "Insert the final board: ";
    for(unsigned int i=0; i<16; i++)
        cin >> finalVec[i];


    Config initialConfig = Config(startVec);
    cout << endl << "Initial Board: " << endl;
    initialConfig.display();

    Config finalConfig = Config(finalVec);
    cout << endl << "Final Board: " << endl;
    finalConfig.display();

    cout << endl;


    clock_t clock1 = 0;
    clock_t clock2 = CLOCKS_PER_SEC; //so that clock2-clock1 doesnt give a stupid result

    if(!strcmp(argv[1], "DFS")){
        clock1 = clock();
        DFS(initialConfig, finalConfig);
        clock2 = clock();
    }
    else if(!strcmp(argv[1], "LDFS")){
        clock1 = clock();
        LDFS(initialConfig, finalConfig, atoi(argv[2]));
        clock2 = clock();
    }
    else if(!strcmp(argv[1], "IDFS")){
        clock1 = clock();
        IDFS(initialConfig, finalConfig, atoi(argv[2]));
        clock2 = clock();
    }
    else if(!strcmp(argv[1], "BFS")){
        clock1 = clock();
        BFS(initialConfig, finalConfig);
        clock2 = clock();
    }
    else if(!strcmp(argv[1], "ASTAR")){
        clock1 = clock();
        ASTAR(initialConfig, finalConfig, atoi(argv[2]));
        clock2 = clock();
    }
    else if (!strcmp(argv[1], "GREEDY")){
        clock1 = clock();
        GREEDY(initialConfig, finalConfig, atoi(argv[2]));
        clock2 = clock();
    }
    else
        cout << "Search method not found" << endl;

    cout << "Execution time: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}
