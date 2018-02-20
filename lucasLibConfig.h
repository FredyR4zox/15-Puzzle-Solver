#include <iostream>
using namespace std;

/*Bibliotecas de Configuração para Jogo dos 15
João Lucas Pires, 201606617*/

//Classe da configuração do tabuleiro
class Config {
private:
	vec

public:
	int pos[4][4]; 
	void display();
	Config(void);
	Config(int[]);
};

//Métodos da classe Config
//Mostra o tabuleiro atual no stdout
void Config::display() {
	cout << "+----------------------+\n";
	cout << "+  " << this->pos[0][0] <<  "|  " << this->pos[0][1] << "  |  " << this->pos[0][2] << "  |  " << this->pos[0][3] << "  +\n";
	cout << "+  " << this->pos[1][0] <<  "|  " << this->pos[1][1] << "  |  " << this->pos[1][2] << "  |  " << this->pos[1][3] << "  +\n";
	cout << "+  " << this->pos[2][0] <<  "|  " << this->pos[2][1] << "  |  " << this->pos[2][2] << " |  " << this->pos[2][3] << "  +\n";
	cout << "+ " << this->pos[3][0] <<  "|  " << this->pos[3][1] << " |  " << this->pos[3][2] << "  | " << this->pos[3][3] << "  +\n";
	cout << "+----------------------+\n";  
}

//Construtores da classe config (para args: void e int[])	
Config::Config(void) {
	int x = 1;
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {		
			if (i == 3 && j == 3) {this->pos[i][j] = -1; break;}
			this->pos[i][j] = x;
			x++;
		}
	}
}

Config::Config(int vec[]) {
	int k = 0;
	for (int i = 0 ; i < 4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			this->pos[i][j] = vec[k];
			k++;
		}
	}
}
