#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

#define EMPTY_SPACE_NUMBER 0

//mudar [] por at()

class Config{
    friend bool operator==(const Config& left, const Config& right);
    friend bool operator!=(const Config& left, const Config& right);

private:
    vector< vector<int> > matrix;
    unsigned int empty_x;
    unsigned int empty_y;

public:
    Config();
    Config(const vector<int> vec);

    vector<char> possibleMoves();
    void move(const char &move);
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
    matrix.at(3).at(3) = EMPTY_SPACE_NUMBER;
    empty_x = 3;
    empty_y = 3;
}

Config::Config(const vector<int> vec){
    for (int i = 0 ; i < 4 ; i++){
        vector<int> vec_aux;
        for (int j = 0 ; j < 4 ; j++){
            vec_aux.push_back(vec[i*4 + j]);
            if(vec.at(i*4 + j) == 0 || vec.at(i*4 + j) == -1){
                empty_x = i;
                empty_y = j;
            }
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
            cout << setw(4) << matrix.at(i).at(j);
        }
        cout << endl;
    }
    cout << "+-----------------+" << endl;  
}

void Config::move(const char &move){
    switch(move){
        case 'u':
            matrix.at(empty_x).at(empty_y) = matrix.at(empty_x-1).at(empty_y);
            matrix.at(empty_x-1).at(empty_y) = 0;
            break;
        case 'd':
            matrix.at(empty_x).at(empty_y) = matrix.at(empty_x+1).at(empty_y);
            matrix.at(empty_x+1).at(empty_y) = 0;
            break;
        case 'l':
            matrix.at(empty_x).at(empty_y) = matrix.at(empty_x).at(empty_y-1);
            matrix.at(empty_x).at(empty_y-1) = 0;
            break;
        case 'r':
            matrix.at(empty_x).at(empty_y) = matrix.at(empty_x).at(empty_y+1);
            matrix.at(empty_x).at(empty_y+1) = 0;
            break;
        default:
            break;
    }
}

vector<char> Config::possibleMoves(){
    vector<char> moves = {'u', 'd', 'l', 'r'};
    vector<char> possibles;

    for(int i=0; i<4; i++){
        if(empty_x==0 && moves[i] == 'u')
            continue;
        else if(empty_x==3 && moves[i] == 'd')
            continue;
        else if(empty_y==0 && moves[i] == 'l')
            continue;
        else if(empty_y==3 && moves[i] == 'r')
            continue;

        possibles.push_back(moves[i]);
    }

    return possibles;
}

bool operator==(const Config& left, const Config& right){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(left.matrix.at(i).at(j) != right.matrix.at(i).at(j))
                return false;
        }
    }
    return true;
}

bool operator!=(const Config& left, const Config& right){
    return !(left == right);
}

//mudar int para unsigned int