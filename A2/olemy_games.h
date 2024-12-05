//
// Created by Yaseen on 12/2/2024.
//

#ifndef A2_OLEMY_GAMES_H
#define A2_OLEMY_GAMES_H

#include "BoardGame_Classes.h"

//Game 5x5_FxF

template <typename T>
class FxF_Board:public Board<T> {
public:
    FxF_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    int counter(T symbol);  //to count number of three longs per symbol
    int who_won();          //to test and see who won, returns number referring to index of player in the players[] array -> X is 0, O is 1

};

template <typename T>
class FxF_manager:public GameManager<T>
{
public:
    void run();
};

template <typename T>
class FxF_Player : public Player<T> {
public:
    FxF_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class FxF_Random_Player : public RandomPlayer<T>{
public:
    FxF_Random_Player (T symbol);
    void getmove(int &x, int &y) ;

};

//--------------------------------- Implementations

template <typename T>
FxF_Board<T>::FxF_Board(){
    this->rows = this->columns = 5;
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
bool FxF_Board<T>::update_board(int x, int y, T mark) {
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
void FxF_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------------------------";
    }
    cout << endl;
}

template <typename T> bool FxF_Board<T>::is_win()
{               //TODO returns if someone won, we specify which player somewhere else

    if(this -> n_moves < 24)
    {
        return false;
    }
    else if(this->n_moves == 24)
    {
        return (counter('X') > counter('O')) || (counter('X') < counter('O'));

    }
}

template <typename T> int FxF_Board<T>::who_won()
{
}

template <typename T> bool FxF_Board<T>::is_draw()
{
    return (this->n_moves > 24 && !is_win());
}

template <typename T> bool FxF_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
int FxF_Board<T>::counter(T mark)
{
    int count = 0;
    for(int i = 1; i < 4; ++i)      //rows
    {
        for(int j = 0; j < 5; ++j)
        {if(this->board[i-1][j] == this->board[i][j] && this->board[i][j] == this->board[i+1][j] && this->board[i-1][j] == mark)
            {
                count++;
            }
        }
    }
    for(int i = 0; i < 5; ++i)      //colums
    {
        for( int j = 1; j < 4; ++j)
        {
            if(this->board[i][j-1] == this->board[i][j] && this->board[i][j] == this->board[i][j+1] && this->board[i][j-1] == mark )
            {
                count++;
            }
        }
    }
    for(int i = 1; i < 4; ++i)      //diagonals same
    {
        for(int j = 1; j < 4; ++j)
        {
            if(this->board[i-1][j-1] == this->board[i][j] && this->board[i][j] == this->board[i+1][j+1] && this->board[i-1][j-1] == mark )
            {
                count++;
            }
        }
    }
    for(int i = 1; i < 4; ++i)      //diagonals diff
    {
        for(int j = 1; j < 4; ++j)
        {
            if(this->board[i-1][j+1] == this->board[i][j] && this->board[i][j] == this->board[i+1][j-1] && this->board[i-1][j+1] == mark )
            {
                count++;
            }
        }
    }
    return count;
}

template <typename T>
FxF_Player<T>::FxF_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FxF_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for FxF_Random_Player
template <typename T>
FxF_Random_Player<T>::FxF_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void FxF_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 4
    y = rand() % this->dimension;
}



#endif //A2_OLEMY_GAMES_H
