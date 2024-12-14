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
class ultimateTTT_board:public Board<T> {
    vector<ultimateTTT_board<T>> miniBoards;

public:
    int counter=1;
    ultimateTTT_board();
    ultimateTTT_board(int x);
    bool update_board(int x, int y, T symbol);
    bool update_miniboard(int x,int y,T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool flag=false;
    T** Board;
    ultimateTTT_board<T>& getminiboard(int index);
    T** getBoard()  {  //to get the board array and sue it in getmove
        return this->board;
    }
    bool setBoard(int x,int y,char symbol); //to change in Board 2d array in getmove
};

template <typename T>
class ultimateTTT_player : public Player<T> {
public:
    ultimateTTT_player(string name, T symbol, Board<T>* board);
    void getmove(int& x, int& y);
};

template <typename T>
class ultimateTTT_randomplayer : public RandomPlayer<T>{
public:
    ultimateTTT_randomplayer (T symbol);
    void getmove(int &x, int &y) ;
};
//implementation////////////////////////////////////////////////////////


template<typename T>
ultimateTTT_board<T>::ultimateTTT_board(int x) {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
} //to prevent overflow (i hope) and to create board 2d array for each mini board

template<typename T>
ultimateTTT_board<T>::ultimateTTT_board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    for (int i=0;i<9;i++) {
        miniBoards.push_back(ultimateTTT_board<T>(1));
    }
}
template <typename T>
bool ultimateTTT_board<T>::setBoard(int x,int y,char symbol) {
    this->board[x][y] = symbol;
}
template <typename T>
ultimateTTT_board<T>& ultimateTTT_board<T>::getminiboard(int index) {
    return miniBoards[index];
}
template <typename T>
void ultimateTTT_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool ultimateTTT_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    char originalvalue=this->board[x][y];
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if(this->board[x][y]=='X'||this->board[x][y]=='O') {
            this->board[x][y]=this->board[x][y];
        }
        if (mark == 0){ //for the main board
            this->n_moves--;
            this->counter--;
            // this->board[x][y] = 0;
        }
        else  {
            this->board[x][y] = toupper(mark);
            this->n_moves++;
            this->counter++;

        }


        return true;
    }
    return false;
}

// template <typename T>
// bool ultimateTTT_board<T>::update_miniboard(int x, int y, T mark) {
//     // Only update if move is valid
//     if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
//         if (mark == 0){
//             this->n_moves--;
//             this->counter--;
//             this->board[x][y] = 0;
//         }
//         else {
//             this->n_moves++;
//             this->counter++;
//             this->board[x][y] = toupper(mark);
//         }
//
//         return true;
//     }
//     return false;
// }
template <typename T>
void ultimateTTT_player<T>::getmove(int& x, int& y) {
    // bool secondflag=true;
    // Store the original board pointer
    Board<T>* originalBoardPtr = this->boardPtr;

    int newboard;
    cout << "Please choose which mini board (0,8): ";
    cin >> newboard;
    ultimateTTT_board<T>* ultimateBoardPtr = dynamic_cast<ultimateTTT_board<T>*>(this->boardPtr);
    if (ultimateBoardPtr) {
        this->boardPtr = &ultimateBoardPtr->getminiboard(newboard); // now points to the miniboard selected by the user
        this->boardPtr->display_board();
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;
        // ultimateBoardPtr->flag=true;
        if(ultimateBoardPtr->counter%2==0) {
            this->boardPtr->update_board(x,y,'O');
        }else if (ultimateBoardPtr->counter%2!=0) {
            this->boardPtr->update_board(x,y,'X');
        }
        // this->boardPtr->update_board(x,y,this->symbol);
        // ultimateBoardPtr->flag=false;
            // Check for a winning move
            if (this->boardPtr->is_win()) {
                if(ultimateBoardPtr->counter%2==0) {
                    originalBoardPtr->update_board(newboard/3,newboard%3,'O');
                    ultimateBoardPtr->counter--;
                }else if (ultimateBoardPtr->counter%2!=0) {
                    originalBoardPtr->update_board(newboard/3,newboard%3,'X');
                    ultimateBoardPtr->counter--;
                }


            }

        this->boardPtr = originalBoardPtr;
        this->symbol=0;
    } else {
        cout << "Error: Invalid board pointer type." << endl;
    }
}

template <typename T>
bool ultimateTTT_board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
            }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
        }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool ultimateTTT_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool ultimateTTT_board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
ultimateTTT_randomplayer<T>::ultimateTTT_randomplayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void ultimateTTT_randomplayer<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
template <typename T>
ultimateTTT_player<T>::ultimateTTT_player(string name, T symbol, Board<T>* board) : Player<T>(name, symbol) {
    this->boardPtr = board;
}
#endif // WORD_TIC_TAC_TOE_H
