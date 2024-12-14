#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
using namespace std;
template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    static int n_moves;
    static int row1;
    static int row2;
    static int row3;
    static int col1;
    static int col2;
    static int col3;
    static bool diag1;
    static bool diag2;
    static int score1;
    static int score2;

};
template <typename T>
int X_O_Board<T>::score1 = 0;
template <typename T>
int X_O_Board<T>::score2 = 0;
template <typename T>
bool X_O_Board<T>::diag2 = false;
template <typename T>
bool X_O_Board<T>::diag1 = false;
template <typename T>
int X_O_Board<T>::n_moves = 0;

template <typename T>
int X_O_Board<T>::row1 = 0;
template <typename T>
int X_O_Board<T>::col1 = 0;
template <typename T>
int X_O_Board<T>::col2 = 1;
template <typename T>
int X_O_Board<T>::col3 = 2;
template <typename T>
int X_O_Board<T>::row2 = 1;
template <typename T>
int X_O_Board<T>::row3=2;
template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;



};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
public:
    X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
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

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    int mov = X_O_Board<T>::n_moves;

    // Check rows
    if(row1!=1) {
        string word = string(1, this->board[row1][0]) + string(1, this->board[row1][1]) + string(1, this->board[row1][2]);
        if (word == "SUS" && this->board[row1][0] != 0) {

            if (n_moves % 2 != 0) {
                score1++;

                row1++;
            } else if(n_moves%2 ==0) {
                score2++;
                row1++;
            }

        }
    }
    if(row2!=2) {
        string word = string(1, this->board[row2][0]) + string(1, this->board[row2][1]) + string(1, this->board[row2][2]);
        if (word == "SUS" && this->board[row2][0] != 0) {

            if (n_moves % 2 != 0) {
                score1++;

                row2++;
            } else if(n_moves%2 ==0) {
                score2++;

                row2++;
            }

        }
    }
    if(row3!=3) {
        string word = string(1, this->board[row3][0]) + string(1, this->board[row3][1]) + string(1, this->board[row3][2]);
        if (word == "SUS" && this->board[row3][0] != 0) {

            if (n_moves % 2 != 0) {
                score1++;

                row3++;
            } else if(n_moves%2 ==0) {
                score2++;

                row3++;
            }

        }
    }
        // Check columns
if(col1!=1) {
    string word2 = string(1, this->board[0][col1]) + string(1, this->board[1][col1]) + string(1, this->board[2][col1]);
    if (word2 == "SUS" && this->board[0][col1] != 0) {

        if (n_moves % 2 != 0) {
            score1++;

            col1++;
        } else if(n_moves%2 ==0){
            score2++;

            col1++;
        }
    }
}
    if(col2!=2) {
        string word2 = string(1, this->board[0][col2]) + string(1, this->board[1][col2]) + string(1, this->board[2][col2]);
        if (word2 == "SUS" && this->board[0][col2] != 0) {

            if (n_moves % 2 != 0) {
                score1++;

                col2++;
            } else if(n_moves%2 ==0){
                score2++;

                col2++;
            }
        }
    }
    if(col3!=3) {
        string word2 = string(1, this->board[0][col3]) + string(1, this->board[1][col3]) + string(1, this->board[2][col3]);
        if (word2 == "SUS" && this->board[0][col3] != 0) {

            if (n_moves % 2 != 0) {
                score1++;

                col3++;
            } else if(n_moves%2 ==0){
                score2++;

                col3++;
            }
        }
    }

        // Check main diagonal
        string word3 = string(1, this->board[0][0]) + string(1, this->board[1][1]) + string(1, this->board[2][2]);
        if (diag1==0 && word3 == "SUS" && this->board[1][1] != 0) {
            diag1 = 5; // Mark main diagonal as scored
            if (n_moves % 2 != 0) {
                score1++;

            } else if(n_moves%2 ==0) {
                score2++;

            }

        }

        // Check anti-diagonal
        string word4 = string(1, this->board[0][2]) + string(1, this->board[1][1]) + string(1, this->board[2][0]);
        if (diag2==0 && word4 == "SUS" && this->board[1][1] != 0) {
            diag2 = 5; // Mark anti-diagonal as scored
            if (n_moves % 2 != 0) {
                score1++;

            } else if(n_moves%2 ==0){
                score2++;

            }
        }
    cout << "Score of player 1: " << score1<< endl;
    cout << "Score of player 2: " << score2<< endl;
    // Winning conditions
    if (n_moves == 8 && (score2 > score1+1)) {

        return true;
    }
    if (n_moves == 9 && (score1 > score2)) {
        return true;

    }
    if (n_moves == 8 && (score2 == score1+1)) {
        return false;
    }
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {

    int count = this->n_moves;
    return (this->n_moves == 9 && this->score1==this->score2 );
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return this->n_moves>=9;
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    // if(this->boardPtr->n_moves==8) {
    //     this->boardPtr->
    // }


}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {

    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H