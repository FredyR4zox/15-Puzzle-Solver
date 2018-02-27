#include <iostream>
#include <array>
#include <cstring>

#include "SearchMethods.h"

using namespace std;

int main(int argc, char const *argv[]){
    if(argc < 2 || (!strcmp(argv[1], "IDFS") && argc!=3) || (!strcmp(argv[1],"ASTAR") && argc !=3) || (!strcmp(argv[1],"GULOSA") && argc != 3) ){
        cout << "Uso: " << argv[0] << " [Método de busca] [Opções de busca]" << endl;
        cout << "Tipos de busca:" << endl;
        cout << "   BFS -> efetua busca em largura;" << endl;
        cout << "   IDFS [Profundidade Máxima] -> efetua busca em profundidade, onde profundidade máxima é o seu limite;" << endl;
        cout << "   DFS -> efetua busca em profundidade;" << endl;
        cout << "   ASTAR [Heurística] -> efetua busca A*;" << endl;
        cout << "   GULOSA [Heurística] -> efetua busca gulosa;" << endl;
        cout << "Tipos de Heurística (ASTAR e GULOSA):" << endl;
        cout << "   0: Nº de peças fora da posição final;" << endl;
        cout << "   1: Manhattan Distance (Somatório das distâncias de cada peça da sua posição final);" << endl;
        cout << "   2: Soma das duas Heurísticas;" << endl;
        return 1;
    }

    array<int, 16> startVec;
    cout << "Insira o tabuleiro inicial: ";
    for(unsigned int i=0; i<16; i++)
        cin >> startVec[i];

    array<int, 16> finalVec;
    cout << "Insira o tabuleiro final: ";
    for(unsigned int i=0; i<16; i++)
        cin >> finalVec[i];


    Config initialConfig = Config(startVec);
    cout << endl << "Tabuleiro Inicial: " << endl;
    initialConfig.display();

    Config finalConfig = Config(finalVec);
    cout << endl << "Tabuleiro Final: " << endl;
    finalConfig.display();

    cout << endl;


    clock_t clock1 = 0;
    clock_t clock2 = CLOCKS_PER_SEC; //so that clock2-clock1 doesnt give a stupid result

    if(!strcmp(argv[1], "DFS")){
        clock1 = clock();
        DFS(initialConfig, finalConfig);
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
    else if (!strcmp(argv[1], "GULOSA")){
        clock1 = clock();
        GREEDY(initialConfig, finalConfig, atoi(argv[2]));
        clock2 = clock();
    }
    else
        cout << "Tipo de busca não existente" << endl;

    cout << "Tempo de execução: " << ((float)clock2-clock1)/CLOCKS_PER_SEC << " segundos" << endl;

    return 0;
}
