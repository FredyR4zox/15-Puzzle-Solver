#include <iostream>
#include <vector>

#include "Config.h"
#include "Move.h"

using namespace std;

/*Bibliotecas de Nós/Nodes (e movimento) para Jogo dos 15*/

//Classe de Nós
/*Os membros de dados são a configuração do tabuleiro, um apontador para o Nó pai,
o movimento que originou este nó, a profundidade do nó, o custo do caminho 
originado e uma fila de nós filhos.*/
class Node{
    friend bool operator==(const Node& left, const Node& right);
    friend bool operator!=(const Node& left, const Node& right);

private:
    Config cfg;
    Node *parent;
    Move last;
    int depth;
    int path_cost;
    //queue<Node> children; //Adicionado à parte - lista com os filhos do nó

public:
    Node();
    Node(vector<int> vec);
    string makePath();
    void display();
    //Move[] verifyMoves();
    void makeChildren();
};

//Métodos para a classe de Nós

//"Getter" para obter a matriz da configuração (que é privada) e não pode ser acedida a partir desta classe.
void Node::display(){
	cfg.display();
}

//Construtores de Nós para void e int[]
Node::Node(){
    cfg = Config();
    parent = NULL;
    last = Move();
	depth = 0;
    path_cost = 0;
    //children = NULL;
}

Node::Node(vector<int> vec){
    cfg = Config(vec);
    parent = NULL;
    last = Move();
    depth = 0;
    path_cost = 0;
    //children = NULL;
}






/*
//Método para verificar movimentos possíveis que retorna um vetor de objetos Move [!!Não Testado!!]
Move[] Node::verifyMoves() 
{
		//O numero de filhos vai ser dado pelo length do vetor de retorno
  int x, y;
  for (int i = 0 ; i < 4 ; i++)
     for (int j = 0 ; j < 4 ; j++)
        if (this->cfg.pos[i][j] == -1)
           x=i;y=j;
       if (i == 0)
       {
         if (j == 0)
         {
           Move r[2];
           r[0] = 'r';
           r[1] = 'd';
           return r;
       }
       else if (j == 1)
       {
           Move r[3];
           r[0] = 'u';
           r[1] = 'r';
           r[2] = 'd';
           return r;
       }
       else
       {
           Move r[2];
           r[0] = 'r';
           r[1] = 'u';
           return r;
       }
   }
   else if (i == 1)
   {
     if (j == 0)
     {
       Move r[3];
       r[0] = 'l';
       r[1] = 'd';
       r[2] = 'r';
       return r;
   }
   else if (j == 1)
   {
       Move r[4];
       r[0] = 'u';
       r[1] = 'r';
       r[2] = 'd';
       r[3] = 'l';
       return r;
   }
   else
   {
       Move r[3];
       r[0] = 'r';
       r[1] = 'u';
       r[2] = 'l';
       return r;
   }
}
else
{
 if (j == 0)
 {
   Move r[2];
   r[0] = 'l';
   r[1] = 'd';
   return r;
}
else if (j == 1)
{
   Move r[3];
   r[0] = 'u';
   r[1] = 'd';
   r[2] = 'l';
   return r;
}
else
{
   Move r[2];
   r[0] = 'u';
   r[1] = 'l';
   return r;
}
}		
}

//Método para criar nós filhos (fila)
void makeChildren() {
	Move possible[] = Node::verifyMoves();
	Node put();
	put.cfg = init;
	put.parent = this;
	put.depth = (this->depth) + 1;
	for (int i = 0 ; i < possible.length() ; i++)
		put.last = possible[i].mv; //CHAR 'o' representa nulo
		this->children.push(put);		
}*/