#include <vector>

#include "SearchMethods.h"

using namespace std;

int main(){
    vector<int> vec;

    for(int i=1; i<16; i++)
        vec.push_back(i);
    vec.push_back(0);

    vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, 13, 14, 15};

    Node node = Node(vec);
    node.display();

    Node node2 = Node(vec2);
    node2.display();

    Config initialConfig = Config(vec2);
    Config finalConfig = Config(vec);

    cout << BFS(initialConfig, finalConfig) << endl;

    return 0;
}