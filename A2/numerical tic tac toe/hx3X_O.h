#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
#include <set>
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
    static set<int> availableNumbers;


};
template <typename T>
int X_O_Board<T>::n_moves = 0;
template <typename T>
set<int> X_O_Board<T>::availableNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

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
            this->board[x][y] = mark;
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
    // Check rows for a sum of 15
    for (int i = 0; i < this->rows; i++) {
        int rowSum = (this->board[i][0] - '0') + (this->board[i][1] - '0') + (this->board[i][2] - '0');
        if (rowSum == 15 && this->board[i][0] != 0) {
            return true;
        }
    }

    // Check columns for a sum of 15
    for (int j = 0; j < this->columns; j++) {
        int colSum = (this->board[0][j] - '0') + (this->board[1][j] - '0') + (this->board[2][j] - '0');
        if (colSum == 15 && this->board[0][j] != 0) {
            return true;
        }
    }

    // Check diagonals for a sum of 15
    int diag1Sum = (this->board[0][0] - '0') + (this->board[1][1] - '0') + (this->board[2][2] - '0');
    int diag2Sum = (this->board[0][2] - '0') + (this->board[1][1] - '0') + (this->board[2][0] - '0');

    if ((diag1Sum == 15 && this->board[1][1] != 0) || (diag2Sum == 15 && this->board[1][1] != 0)) {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {

    int count = this->n_moves;
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    char num1;
    int av;
    int movecount =X_O_Board<T>::n_moves;

    if(movecount%2==0) {
        int count=0;
        while(count!=1) {
            cout<<"enter an odd available number from (1 to 9): \n";
            cin>>av;
            if(av%2!=0 && (X_O_Board<T>::availableNumbers.find(av) !=X_O_Board<T>::availableNumbers.end())&& 1<=av<=9) {
                count = 1;
                X_O_Board<T>::availableNumbers.erase(av);
            }
            else cout<<"enter another number!"<<endl;

        }
    }
    if(movecount%2!=0) {
        int count=0;
        while(count!=1) {
            cout<<"enter an even available number from (1 to 9) : \n";
            cin>>av;
            if(av%2==0 &&(X_O_Board<T>::availableNumbers.find(av) !=X_O_Board<T>::availableNumbers.end()) && 1<=av<=9) {
                count = 1;
                X_O_Board<T>::availableNumbers.erase(av);
            }
            else cout<<"enter another number!"<<endl;
        }
    }

    this->symbol = av+ '0';

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
    // Generate random x and y for move placement
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

    int move = X_O_Board<T>::n_moves;
    vector<int> evenNumbers;
    vector<int> oddnum;

    // Separate even and odd numbers from availableNumbers
    for (int num : X_O_Board<T>::availableNumbers) {
        if (num % 2 == 0) {
            evenNumbers.push_back(num);
        } else {
            oddnum.push_back(num);
        }
    }

    if (move % 2 != 0 && !evenNumbers.empty()) {
        int ind = rand() % evenNumbers.size();
        int evn = evenNumbers[ind];
        this->symbol = evn + '0';  // Update the symbol with the even number selected
        X_O_Board<T>::availableNumbers.erase(evn);  // Remove from available numbers
    }
    else if (move % 2 == 0 && !oddnum.empty()) {
        int ind1 = rand() % oddnum.size();
        int odd = oddnum[ind1];
        this->symbol = odd + '0';  // Update the symbol with the odd number selected
        X_O_Board<T>::availableNumbers.erase(odd);  // Remove from available numbers
    }
}







#endif //_3X3X_O_H