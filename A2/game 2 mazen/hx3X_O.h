//
// Created by mazen amr on 11/30/2024.
//

#ifndef HX3X_O_H
#define HX3X_O_H
#include "BoardGame_Classes.h"

template <typename T>
class X_O_Board:public Board<T> {
public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

    int getRows() const { return this->rows; }
    int getColumns() const { return this->columns; }
    T getCell(int x, int y) const { return this->board[x][y]; }
    void setCell(int x, int y, T value) { this->board[x][y] = value; }
};

template <typename T>
class X_O_Player : public Player<T> {
private:
    X_O_Board<T>& board;
public:
    X_O_Player (string name, T symbol,X_O_Board<T>& b);
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
    this->rows =6;
    this->columns = 7;
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
        // cout<<this->rows<<endl; =6
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------------------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] != 0 &&this->board[i][j] == this->board[i][j + 1] &&this->board[i][j] == this->board[i][j + 2] &&this->board[i][j] == this->board[i][j + 3]) {
                return true;
                }
        }
    }
    for (int i = 0; i < this->columns; i++) {
        for (int j = 0; j < this->rows - 3; j++) {
            if (this->board[j][i] != 0 &&this->board[j][i] == this->board[j + 1][i] &&this->board[j][i] == this->board[j + 2][i] &&this->board[j][i] == this->board[j + 3][i]) {
                return true;
                }
        }
    }
    // Check diagonal (bottom-left to top-right)
    for (int r = 3; r < this->rows; r++) {
        for (int c = 0; c < this->columns - 3; c++) {
            if (this->board[r][c] != 0 &&this->board[r][c] == this->board[r - 1][c + 1] &&this->board[r][c] == this->board[r - 2][c + 2] &&this->board[r][c] == this->board[r - 3][c + 3]) {
                return true;
                }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int r = 0; r < this->rows - 3; r++) {
        for (int c = 0; c < this->columns - 3; c++) {
            if (this->board[r][c] != 0 &&this->board[r][c] == this->board[r + 1][c + 1] &&this->board[r][c] == this->board[r + 2][c + 2] &&this->board[r][c] == this->board[r + 3][c + 3]) {
                return true;
                }
        }
    }

    return false;
}

// Return true if 42 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol, X_O_Board<T>& b)
    : Player<T>(name, symbol), board(b) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    while (true) { // Loop until a valid move is made
        cout << "\nPlease enter your move column (0 to 6): ";
        cin >> y; // Get the column from the user

        // Check if the column is within valid range
        if (y < 0 || y >= this->board.getColumns()) {
            cout << "Invalid column. Please choose a column between 0 and " << (this->board.getColumns() - 1) << "." << endl;
            continue;
        }

        // Find the lowest available row in the specified column
        x = -1; // Initialize x to an invalid value
        for (int i = this->board.getRows() - 1; i >= 0; i--) { // Start from the bottom row
            if (this->board.getCell(i, y) == 0) { // Check if the cell is empty
                x = i; // Set x to the lowest available row
                break; // Exit the loop once we find the lowest available row
            }
        }

        // If a valid row is found, update the board and break the loop
        if (x != -1) {
            this->board.update_board(x, y, this->symbol); // Update the board with the player's symbol
            this->board.display_board(); // Display the updated board
            break;
        } else {
            cout << "Column " << y << " is full. Please choose another column." << endl;
        }
    }
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 6;  // Random number between 0 and 5
    y = rand() % this->dimension; // random number between 0 and 6
}








#endif //HX3X_O_H