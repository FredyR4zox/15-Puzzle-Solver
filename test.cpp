#include <vector>

#include "SearchMethods.h"

using namespace std;

int main(){
    vector<int> vec;

    for(int i=1; i<16; i++)
        vec.push_back(i);
    vec.push_back(0);

    vector<int> vec2;

    for(int i=1; i<16; i++)
        vec2.push_back(i);
    vec2.push_back(0);
    vec2[15] = 12;
    vec2[11] = 0;


    Node node = Node(vec);
    node.display();

    Node node2 = Node(vec2);
    node2.display();

    Config initialConfig = Config(vec2);
    Config finalConfig = Config(vec);

    BFS(initialConfig, finalConfig);

    return 0;
}