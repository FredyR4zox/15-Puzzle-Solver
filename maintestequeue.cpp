#include <iostream>
#include "Node.h"
using namespace std;

/*Programa de Teste para Jogo dos 15
João Lucas Pires, 201606617*/

int main(void) {
	queue<Node> fila;
	int vec[16] = {0, 1 , 2 , 3, 4 ,5 , 6, 7, 8, 9, 10 ,11 ,12 ,13, 14, -1};
	Node test(vec);
	fila.push(test);
	fila.front().displayCFG();
	return 0;
}

//Função de pesquisa geral
/*ALGORITMO FINAL NAO MEXER!!! W.I.P*/
Path generalSearchAlgorithm(/*SearchFN*/,Config init, Config final) {
	if (!verifySolubility(init,final))
		return ; /*Impossible to find solution*/
	queue<Node> path;
	/*Construir primeiro node*/
	Node ini(); //Node inicial
	ini.cfg = init;
	ini.parent = NULL;
	ini.last = 'o'; /*CHAR 'o' representa nulo*/
	ini.depth = 0;
	path.push(ini); //Arranjar isto, inicializar o primeiro nó
	while (!path.empty()) {
		Node x = path.pop();
		if (x.cfg == final) /*falta fazer a funçao comparator para configs*/
			return path.makeChildren();
		list<Node> descendant = makeDescendants(node);
		insert(descendant,path,/*SearchFN*/);
	}
	return ; /*Solution not found*/
}