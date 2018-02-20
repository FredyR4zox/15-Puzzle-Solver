#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//mudar [] por at()

class Config{
	friend bool operator==(const Config& left, const Config& right);
    friend bool operator!=(const Config& left, const Config& right);
    
private:
    vector< vector<int> > matrix;

public:
    Config();
    Config(vector<int> vec);

    void display();
};

//Construtores da classe config (para args: void e int[])   
Config::Config(){
    for (int i = 0 ; i < 4 ; i++){
    	vector<int> vec;
        for (int j = 0 ; j < 4 ; j++){
           vec.push_back(i*4 + j + 1);
        }
        matrix.push_back(vec);
    }
    matrix[3][3] = 0; //ou -1
}

Config::Config(vector<int> vec){
    for (int i = 0 ; i < 4 ; i++){
    	vector<int> vec_aux;
        for (int j = 0 ; j < 4 ; j++){
            vec_aux.push_back(vec[i*4 + j]);
        }
        matrix.push_back(vec_aux);
    }
}

//Métodos da classe Config
//Mostra o tabuleiro atual no stdout
void Config::display(){
    cout << "+-----------------+" << endl;
    for(int i=0; i<4; i++){
    	for(int j=0; j<4; j++){
    		cout << setw(4) << matrix[i][j];
    	}
    	cout << endl;
    }
    cout << "+-----------------+" << endl;  
}

bool operator==(const Config& left, const Config& right){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(left.matrix[i][j] != right.matrix[i][j])
				return false;
		}
	}

	return true;
}
bool operator!=(const Config& left, const Config& right){
	return !(left == right);
}