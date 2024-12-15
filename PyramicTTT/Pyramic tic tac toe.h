#ifndef WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <map>
#include <fstream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>
using namespace std;
template <typename T>
class pyramicTTT_board:public Board<T> {
    vector<vector<char>> board;

public:
    pyramicTTT_board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class pyramicTTT_player:public Player<T> {
public:
    pyramicTTT_player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class pyramicTTT_randomplayer:public RandomPlayer<T> {
public:
    pyramicTTT_randomplayer (T symbol);
    void getmove(int &x, int &y) ;
};

//-----------implementation----------
template<typename T>
pyramicTTT_board<T>::pyramicTTT_board() {
    this->rows=3;
    this->columns=5;
    this->n_moves=0;
    this->board={{' '},{' ',' ',' '},{' ',' ',' ',' ',' '}};
}
template <typename T>
bool pyramicTTT_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] ==' '|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] =' ';
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void pyramicTTT_board<T>::display_board() {
    cout<<setw(16)<<"("<<0<<","<<0<<") ";
    cout<<this->board[0][0];
    cout << endl;
    for(int i=0;i<3;i++) {
        cout<<setw(6)<<"("<<1<<","<<i<<") ";
        cout<<this->board[1][i];
    }
    cout<<endl;
    for(int i=0;i<5;i++) {
        cout<<setw(3)<<"("<<2<<","<<i<<")";
        cout<<this->board[2][i];
    }
    cout<<endl;

}

template <typename T>
bool pyramicTTT_board<T>::is_win() {  //will be implemented--------------------------------------------
    // Check column
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && this->board[0][0] != ' ') {
        return true;
    }
    //check second level
    for(int i=0;i<3;i++) {
        if(board[1][0]==board[1][1] && board[1][1]==board[1][2]&& this->board[1][i] != ' ') {
            return true;
        }
    }

    //check third level
    for(int i=0;i<5;i++) {

        if(board[2][i]==board[2][i+1] && board[2][i+1]==board[2][i+2] && this->board[2][i] != ' ') {
            return true;
        }
    }
    //check diagonal
    if(board[0][0]==board[1][2] && board[1][2]==board[2][4] && this->board[0][0] != ' ' || board[0][0]==board[1][0] && board[1][0]==board[2][0] && this->board[0][0] != ' ') {
        return true;
    }
    return false;
}
template <typename T>
bool pyramicTTT_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool pyramicTTT_board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
pyramicTTT_player<T>::pyramicTTT_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void pyramicTTT_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
pyramicTTT_randomplayer<T>::pyramicTTT_randomplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void pyramicTTT_randomplayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
#endif
