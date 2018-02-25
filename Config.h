/*Board Libraries for the 15-Puzzle
It contains a 3 Dimensional-Vector to store the position
of the pieces and two unsigned int variables that hold
the coordinated where the empty space is located*/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//Number that defined the empty space in the board (can also be -1)
#define EMPTY_SPACE_NUMBER 0

class Config{
    friend bool operator==(const Config& left, const Config& right);
    friend bool operator!=(const Config& left, const Config& right);

private:
    vector< vector<int> > matrix;
    unsigned int emptyRowIndex;   //x position of the empty space
    unsigned int emptyColumnIndex;   //y position of the empty space

public:
    Config();
    Config(const vector<int> vec);

    vector< vector<int> > getMatrix() const;
    unsigned int getEmptyRowIndex() const;
    unsigned int getEmptyColumnIndex() const;

    void display();
    vector<char> possibleMoves();
    void move(const char &move);
};



//Constructors for the Config class (for args: void and vector<int>) 
Config::Config(){
    for(unsigned int i = 0 ; i < 4 ; i++){
        vector<int> vec;
        for(unsigned int j = 0 ; j < 4 ; j++){
            vec.push_back(i*4 + j + 1);
        }
        matrix.push_back(vec);
    }
    matrix.at(3).at(3) = EMPTY_SPACE_NUMBER;
    emptyRowIndex = 3;
    emptyColumnIndex = 3;
}

Config::Config(const vector<int> vec){
    for(unsigned int i = 0 ; i < 4 ; i++){
        vector<int> vec_aux;
        for(unsigned int j = 0 ; j < 4 ; j++){
            vec_aux.push_back(vec[i*4 + j]);
            if(vec.at(i*4 + j) == EMPTY_SPACE_NUMBER){
                emptyRowIndex = i;
                emptyColumnIndex = j;
            }
        }
        matrix.push_back(vec_aux);
    }
}



//Methods of the Config Class
vector< vector<int> > Config::getMatrix() const{
    return matrix;
}

unsigned int Config::getEmptyRowIndex() const{
    return emptyRowIndex;
}

unsigned int Config::getEmptyColumnIndex() const{
    return emptyColumnIndex;
}



//Print the board on stdout
void Config::display(){
    cout << "+-----------------+" << endl;
    for(unsigned int i=0; i<4; i++){
        for(unsigned int j=0; j<4; j++){
            cout << setw(4) << matrix.at(i).at(j);
        }
        cout << endl;
    }
    cout << "+-----------------+" << endl;  
}

//Return a vector with all the possible moves from the current position
vector<char> Config::possibleMoves(){
    vector<char> moves = {'u', 'd', 'l', 'r'};
    vector<char> possibles;

    for(unsigned int i=0; i<4; i++){
        if(emptyRowIndex==0 && moves.at(i) == 'u')
            continue;
        else if(emptyRowIndex==3 && moves.at(i) == 'd')
            continue;
        else if(emptyColumnIndex==0 && moves.at(i) == 'l')
            continue;
        else if(emptyColumnIndex==3 && moves.at(i) == 'r')
            continue;

        possibles.push_back(moves.at(i));
    }

    return possibles;
}

//Move the empty space
void Config::move(const char &move){
    switch(move){
        case 'u':
            matrix.at(emptyRowIndex).at(emptyColumnIndex) = matrix.at(emptyRowIndex-1).at(emptyColumnIndex);
            matrix.at(emptyRowIndex-1).at(emptyColumnIndex) = 0;
            emptyRowIndex-=1;
            break;
        case 'd':
            matrix.at(emptyRowIndex).at(emptyColumnIndex) = matrix.at(emptyRowIndex+1).at(emptyColumnIndex);
            matrix.at(emptyRowIndex+1).at(emptyColumnIndex) = 0;
            emptyRowIndex+=1;
            break;
        case 'l':
            matrix.at(emptyRowIndex).at(emptyColumnIndex) = matrix.at(emptyRowIndex).at(emptyColumnIndex-1);
            matrix.at(emptyRowIndex).at(emptyColumnIndex-1) = 0;
            emptyColumnIndex-=1;
            break;
        case 'r':
            matrix.at(emptyRowIndex).at(emptyColumnIndex) = matrix.at(emptyRowIndex).at(emptyColumnIndex+1);
            matrix.at(emptyRowIndex).at(emptyColumnIndex+1) = 0;
            emptyColumnIndex+=1;
            break;
        default:
            break;
    }
}



//Operator Overloading functions to simplify the code
bool operator==(const Config& left, const Config& right){
    for(unsigned int i=0; i<4; i++){
        for(unsigned int j=0; j<4; j++){
            if(left.matrix.at(i).at(j) != right.matrix.at(i).at(j))
                return false;
        }
    }
    return true;
}

bool operator!=(const Config& left, const Config& right){
    return !(left == right);
}