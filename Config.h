#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

#define EMPTY_SPACE_NUMBER 0

class Config{
    friend bool operator==(const Config& left, const Config& right);
    friend bool operator!=(const Config& left, const Config& right);

private:
    vector< vector<int> > matrix;
    unsigned int empty_x;   //posição do sitio onde está o espaço vazio
    unsigned int empty_y;

public:
    Config();
    Config(const vector<int> vec);

    void display();
    vector<char> possibleMoves();
    void move(const char &move);
};

//Construtores da classe config (para args: void e vector<int>)   
Config::Config(){
    for (unsigned int i = 0 ; i < 4 ; i++){
        vector<int> vec;
        for (unsigned int j = 0 ; j < 4 ; j++){
            vec.push_back(i*4 + j + 1);
        }
        matrix.push_back(vec);
    }
    matrix.at(3).at(3) = EMPTY_SPACE_NUMBER;
    empty_x = 3;
    empty_y = 3;
}

Config::Config(const vector<int> vec){
    for (unsigned int i = 0 ; i < 4 ; i++){
        vector<int> vec_aux;
        for (unsigned int j = 0 ; j < 4 ; j++){
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
    for(unsigned int i=0; i<4; i++){
        for(unsigned int j=0; j<4; j++){
            cout << setw(4) << matrix.at(i).at(j);
        }
        cout << endl;
    }
    cout << "+-----------------+" << endl;  
}

vector<char> Config::possibleMoves(){
    vector<char> moves = {'u', 'd', 'l', 'r'};
    vector<char> possibles;

    for(unsigned int i=0; i<4; i++){
        if(empty_x==0 && moves.at(i) == 'u')
            continue;
        else if(empty_x==3 && moves.at(i) == 'd')
            continue;
        else if(empty_y==0 && moves.at(i) == 'l')
            continue;
        else if(empty_y==3 && moves.at(i) == 'r')
            continue;

        possibles.push_back(moves.at(i));
    }

    return possibles;
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