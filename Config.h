/*Board Libraries for the 15-Puzzle
It contains a 3 Dimensional-Vector to store the position
of the pieces and two unsigned int variables that hold
the coordinated where the empty space is located*/

#include <iostream>
#include <iomanip>
#include <array>

using namespace std;

//Number that defined the empty space in the board (can also be -1)
#define EMPTY_SPACE_NUMBER 0

class Config{
    friend inline bool operator==(const Config& left, const Config& right);
    friend inline bool operator!=(const Config& left, const Config& right);

private:
    array< array<int, 4>, 4> matrix;
    unsigned int emptyRowIndex;   //x position of the empty space
    unsigned int emptyColumnIndex;   //y position of the empty space

public:
    Config();
    Config(const array<int, 16>& arr);

    inline array< array<int, 4>, 4> getMatrix() const;
    inline unsigned int getEmptyRowIndex() const;
    inline unsigned int getEmptyColumnIndex() const;

    void display();
    array<char, 4> possibleMoves();
    void move(const char& move);
};



//Constructors for the Config class (for args: void and vector<int>) 
Config::Config(){
    for(unsigned int i = 0; i < 4; i++){
        for(unsigned int j = 0; j < 4; j++)
            matrix[i][j] = i*4 + j + 1;
    }

    matrix[3][3] = EMPTY_SPACE_NUMBER;
    emptyRowIndex = 3;
    emptyColumnIndex = 3;
}

Config::Config(const array<int, 16>& arr){
    for(unsigned int i = 0; i < 4; i++){
        for(unsigned int j = 0; j < 4; j++){
            matrix[i][j] = arr[i*4 + j];
            if(arr[i*4 + j] == EMPTY_SPACE_NUMBER){
                emptyRowIndex = i;
                emptyColumnIndex = j;
            }
        }
    }
}



//Methods of the Config Class
inline array< array<int, 4>, 4> Config::getMatrix() const{
    return matrix;
}

inline unsigned int Config::getEmptyRowIndex() const{
    return emptyRowIndex;
}

inline unsigned int Config::getEmptyColumnIndex() const{
    return emptyColumnIndex;
}



//Print the board on stdout
void Config::display(){
    cout << "+-----------------+" << endl;
    for(unsigned int i=0; i<4; i++){
        for(unsigned int j=0; j<4; j++){
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
    cout << "+-----------------+" << endl;  
}

//Return a vector with all the possible moves from the current position
array<char, 4> Config::possibleMoves(){
    array<char, 4> moves = {'u', 'd', 'l', 'r'};
    array<char, 4> possibles = {};
    unsigned int index = 0;

    for(unsigned int i=0; i<4; i++){
        if(emptyRowIndex==0 && moves[i] == 'u')
            continue;
        else if(emptyRowIndex==3 && moves[i] == 'd')
            continue;
        else if(emptyColumnIndex==0 && moves[i] == 'l')
            continue;
        else if(emptyColumnIndex==3 && moves[i] == 'r')
            continue;

        possibles[index] = moves[i];
        index++;
    }

    return possibles;
}

//Move the empty space
void Config::move(const char& move){
    switch(move){
        case 'u':
            matrix[emptyRowIndex][emptyColumnIndex] = matrix[emptyRowIndex-1][emptyColumnIndex];
            matrix[emptyRowIndex-1][emptyColumnIndex] = 0;
            emptyRowIndex-=1;
            break;
        case 'd':
            matrix[emptyRowIndex][emptyColumnIndex] = matrix[emptyRowIndex+1][emptyColumnIndex];
            matrix[emptyRowIndex+1][emptyColumnIndex] = 0;
            emptyRowIndex+=1;
            break;
        case 'l':
            matrix[emptyRowIndex][emptyColumnIndex] = matrix[emptyRowIndex][emptyColumnIndex-1];
            matrix[emptyRowIndex][emptyColumnIndex-1] = 0;
            emptyColumnIndex-=1;
            break;
        case 'r':
            matrix[emptyRowIndex][emptyColumnIndex] = matrix[emptyRowIndex][emptyColumnIndex+1];
            matrix[emptyRowIndex][emptyColumnIndex+1] = 0;
            emptyColumnIndex+=1;
            break;
        default:
            break;
    }
}



//Operator Overloading functions to simplify the code
inline bool operator==(const Config& left, const Config& right){
    for(unsigned int i=0; i<4; i++){
        for(unsigned int j=0; j<4; j++){
            if(left.matrix[i][j] != right.matrix[i][j])
                return false;
        }
    }
    return true;
}

inline bool operator!=(const Config& left, const Config& right){
    return !(left == right);
}

namespace std{
    template <>
    struct hash<Config>{
        size_t operator()(const Config& cfg) const noexcept{
            size_t hash = 0;
            for(unsigned int i=0; i<4; i++){
                for(unsigned int j=0; j<4; j++)
                    hash = (hash * 256 + cfg.getMatrix()[i][j]) % 16;
            }

            return hash;
        }
    };
}