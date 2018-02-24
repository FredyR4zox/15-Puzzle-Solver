#include <vector>
#include <limits>

#include "SearchMethods.h"

using namespace std;

int main(){
    Node node = Node();
    node.display();

    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 13, 14, 15};
    Node node2 = Node(vec2);
    node2.display();

    Config initialConfig = Config(vec2);
    Config finalConfig = Config();

    //cout << IDFS(initialConfig, finalConfig, numeric_limits<unsigned>::max()) << endl;
    clock_t clock1 = clock();
    cout << "DFS path: " << DFS(initialConfig, finalConfig) << endl;
    clock_t clock2 = clock();
    cout << "BFS path: " << BFS(initialConfig, finalConfig) << endl;
    clock_t clock3 = clock();
    cout << "LDFS path: " << LDFS(initialConfig, finalConfig, 25) << endl;
    clock_t clock4 = clock();
    cout << "IDFS path: " << IDFS(initialConfig, finalConfig, 25) << endl;
    clock_t clock5 = clock();
    cout << "A* path: " << ASTAR(initialConfig, finalConfig) << endl;
    clock_t clock6 = clock();


    cout << "Tempo de execução para DFS: " << clock2-clock1 << endl;
    cout << "Tempo de execução para BFS: " << clock3-clock2 << endl;
    cout << "Tempo de execução para LDFS: " << clock4-clock3 << endl;
    cout << "Tempo de execução para IDFS: " << clock5-clock4 << endl;
    cout << "Tempo de execução para ASTAR: " << clock6-clock5 << endl;

    return 0;
}