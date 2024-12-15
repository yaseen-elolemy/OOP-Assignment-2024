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
class wordTTT_Board : public Board<T> {
    map<string, string> words;
    fstream file;
public:
    wordTTT_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class wordTTT_Player : public Player<T> {
public:
    wordTTT_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class wordTTT_Random_Player : public RandomPlayer<T> {
public:
    wordTTT_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

//----------Implementation-------------

template <typename T>
wordTTT_Board<T>::wordTTT_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    file.open("dic.txt", ios::in);
    string value;
    while (file >> value) {
        words[value] = value;
    }
}

template <typename T>
bool wordTTT_Board<T>::update_board(int x, int y, T Letter) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || Letter == 0)) {
        if (Letter == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(Letter);
        }
        return true;
    }
    return false;
}

template <typename T>
void wordTTT_Board<T>::display_board() {
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
bool wordTTT_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((words.find(string(1, this->board[i][0]) + this->board[i][1] + this->board[i][2]) != words.end() && this->board[i][0] != 0) ||
            (words.find(string(1, this->board[0][i]) + this->board[1][i] + this->board[2][i]) != words.end() && this->board[0][i] != 0)) {
            return true;
            }
    }

    // Check diagonals
    if ((words.find(string(1, this->board[0][0]) + this->board[1][1] + this->board[2][2]) != words.end() && this->board[0][0] != 0) ||
        (words.find(string(1, this->board[0][2]) + this->board[1][1] + this->board[2][0]) != words.end() && this->board[0][2] != 0)) {
        return true;
        }

    return false;
}

template <typename T>
bool wordTTT_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool wordTTT_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
wordTTT_Player<T>::wordTTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void wordTTT_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "Please enter the letter: ";
    T letter;
    cin >> letter;
    this->symbol=letter;
}

template <typename T>
wordTTT_Random_Player<T>::wordTTT_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void wordTTT_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    this->symbol = 'A' + (rand() % 26);  // Random letter between 'A' and 'Z'
}
#endif
