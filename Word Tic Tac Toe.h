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
class ultimateTTT_board : public Board<T> {
    int miniB;
protected:
    vector<ultimateTTT_board<T>> miniBoards;
    vector<vector<T>> allBoards;  // Vector to hold the main board and mini boards
    T** currentBoard;  // Pointer to the current board
public:
    ultimateTTT_board();
    ultimateTTT_board(int x);
    bool update_board(int x, int y, T symbol);
    bool update_mini_board(int index,int x, int y, T symbol);
    void display_board();
    void display_mini_board(int miniB);
    bool is_win();
    bool is_win_miniboard(int k);
    bool is_draw();
    bool game_is_over();
    vector<ultimateTTT_board<T>>& getMiniBoards(); // Corrected method declaration
    T getCell(int row, int col) const;
};

template <typename T>
class ultimateTTT_player:public Player<T> {

public:
    ultimateTTT_player (string name, T symbol);
    void getmove(int& x, int& y) ;
    void set_miniB(int newMiniB); // Setter method to change miniB

};

template <typename T>
class ultimateTTT_randomplayer:public RandomPlayer<T> {
public:
    ultimateTTT_randomplayer (T symbol);
    void getmove(int &x, int &y) ;
};

//---------------implementation------------------
template<typename T>
ultimateTTT_board<T>::ultimateTTT_board() {
    this->miniB = 0;                  // Initialize miniB
    this->n_moves = 0;               // Initialize number of moves
    this->rows = this->columns = 3;  // Set dimensions of the ultimate board
    vector<T> mainBoard(9,0);
    allBoards.push_back(mainBoard);
    for (int i = 0; i < 9; ++i) {
        miniBoards.push_back(ultimateTTT_board<T>(1));
        vector<T> miniBoard(9, 0);
        allBoards.push_back(miniBoard);
    }

}
template<typename T>
ultimateTTT_board<T>::ultimateTTT_board(int x) {} //to prevent overflow (i hope)


template <typename T>
vector<ultimateTTT_board<T>>& ultimateTTT_board<T>::getMiniBoards() {
    return miniBoards;
}
template <typename T>
void ultimateTTT_board<T>::display_board() {
    for (int i = 0; i < 3; i++) {
        cout << "\n| ";
        for (int j = 0; j < 3; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << allBoards[0][i*3 +j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template <typename T>
void ultimateTTT_board<T>::display_mini_board(int index) {
    for (int i = 0; i < 3; i++) {
        cout << "\n| ";
        for (int j = 0; j < 3; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << allBoards[index+1][i*3 +j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template<typename T>
void ultimateTTT_player<T>::set_miniB(int newMiniB) {
    if (newMiniB >= 0 && newMiniB < 9) {
        this->miniB = newMiniB;
    } else {
        cout <<"Invalid mini board index. Please choose a value between 0 and 8"<<endl;
    }
}
// template <typename T>
// void ultimateTTT_player<T>::display_mini_board(int miniB) {
//     Board<T>* miniBoard = this->tempBoard->getMiniBoards()[miniB];
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             cout << miniBoard->board[i][j] << " ";
//         }
//         cout << endl;
//     }
// }
template <typename T>
ultimateTTT_player<T>::ultimateTTT_player(string name, T symbol) : Player<T>(name, symbol) {
}

template <typename T>
void ultimateTTT_player<T>::getmove(int& x, int& y) {
    // Store the original board pointer
    Board<T>* originalBoardPtr = this->boardPtr;
    int newboard;
    cout << "Please choose which mini board (0,8): ";
    cin >> newboard;

    // Cast boardPtr to ultimateTTT_board<T>* to access display_mini_board and update_mini_board
    ultimateTTT_board<T>* ultimateBoardPtr = dynamic_cast<ultimateTTT_board<T>*>(this->boardPtr);
    ultimateBoardPtr->display_mini_board(newboard);

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    this->boardPtr->update_board(x, y, this->symbol);
    if (ultimateBoardPtr->is_win_miniboard(newboard + 1)) {
        this->boardPtr = originalBoardPtr;
        ultimateBoardPtr->update_mini_board(newboard, newboard / 3, newboard % 3, this->symbol);
    }
    // Reset the boardPtr to the original board
    this->boardPtr = originalBoardPtr;
}

// Constructor for X_O_Random_Player
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
bool ultimateTTT_board<T>::is_win() {
    // Check rows and columns for the main board
    for (int i = 0; i < this->rows; i++) {
        if ((allBoards[0][i * 3] == allBoards[0][i * 3 + 1] && allBoards[0][i * 3 + 1] == allBoards[0][i * 3 + 2] && allBoards[0][i * 3] != 0) ||
            (allBoards[0][i] == allBoards[0][i + 3] && allBoards[0][i + 3] == allBoards[0][i + 6] && allBoards[0][i] != 0)) {
            return true;
            }
    }

    // Check diagonals for the main board
    if ((allBoards[0][0] == allBoards[0][4] && allBoards[0][4] == allBoards[0][8] && allBoards[0][0] != 0) ||
        (allBoards[0][2] == allBoards[0][4] && allBoards[0][4] == allBoards[0][6] && allBoards[0][2] != 0)) {
        return true;
        }

    return false;
}
template <typename T>
bool ultimateTTT_board<T>::is_win_miniboard(int k) {
    // Check rows and columns for the main board
    for (int i = 0; i < this->rows; i++) {
        if ((allBoards[k][i * 3] == allBoards[k][i * 3 + 1] && allBoards[k][i * 3 + 1] == allBoards[k][i * 3 + 2] && allBoards[k][i * 3] != 0) ||
            (allBoards[k][i] == allBoards[k][i + 3] && allBoards[k][i + 3] == allBoards[k][i + 6] && allBoards[k][i] != 0)) {
            return true;
            }
    }

    // Check diagonals for the main board
    if ((allBoards[k][0] == allBoards[k][4] && allBoards[k][4] == allBoards[k][8] && allBoards[k][0] != 0) ||
        (allBoards[k][2] == allBoards[k][4] && allBoards[k][4] == allBoards[k][6] && allBoards[k][2] != 0)) {
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
bool ultimateTTT_board<T>::update_board(int x, int y, T mark) {
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
template <typename T>
bool ultimateTTT_board<T>::update_mini_board(int index, int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->allBoards[index+1][x*3 +y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->allBoards[index+1][x*3 +y] = 0;
        }
        else {
            this->n_moves++;
            this->allBoards[index+1][x*3 +y] = toupper(mark);
        }

        return true;
    }
    return false;
}
#endif // WORD_TIC_TAC_TOE_H