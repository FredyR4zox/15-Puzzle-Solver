//Classe para representação do movimento

using namespace std;

class Move{
    friend bool operator==(const Move& left, const Move& right);
    friend bool operator!=(const Move& left, const Move& right);

private:
    char mv; //Start: 'a'; Up: 'u'; Down: 'd'; Left: 'l'; Right: 'r'

public:
    Move();
    Move(const char &move);
    char getMove() const;
};

//Métodos da classe Move
//Construtor default para a classe Move
Move::Move(){
    mv = 'a';
}

Move::Move(const char &move){
    mv = move;
}

//Método para retornar o movimento como char
char Move::getMove() const{
    return mv;
}

bool operator==(const Move& left, const Move& right){
    return (left.mv == right.mv);
}

bool operator!=(const Move& left, const Move& right){
    return !(left.mv == right.mv);
}