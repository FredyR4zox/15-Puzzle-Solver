#include <vector>

#include "Node.h"

using namespace std;

int main(){
	vector<int> vec;
	
	for(int i=1; i<16; i++)
		vec.push_back(i);
	vec.push_back(0);

	Node node = Node(vec);

	node.display();

	return 0;
}