//
// Created by Yaseen on 12/15/2024.
//

#ifndef A2_GAMES_H
#define A2_GAMES_H

#include "BoardGame_Classes.h"

#include "BoardGame_Classes.h"
#include <map>
#include <fstream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>
using namespace std;
template <typename T>
class ultimateTTT_board:public Board<T> {
    vector<ultimateTTT_board<T>> miniBoards; //contains all 9 miniboards 3x3

public:
    int counter=1; //counter similar to n_moves
    ultimateTTT_board(); //default constructor
    ultimateTTT_board(int x); //constructor for the mini boards to prevent overflow
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    void display_allboards(); //to display all boards
    ultimateTTT_board<T>& getminiboard(int index); //to get the miniboard from the miniboards array
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
    ultimateTTT_randomplayer (T symbol,Board<T>* board);

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
}

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
        miniBoards.push_back(ultimateTTT_board<T>(1)); //add 9 miniboards to the vector
    }
}

template <typename T>
void ultimateTTT_board<T>::display_allboards() { //to display all boards
    for (int i = 0; i < miniBoards.size(); i++) {
        cout <<"Mini Board "<<i<<":\n";
        miniBoards[i].display_board();
        cout <<endl;
    }
}

template <typename T>
ultimateTTT_board<T>& ultimateTTT_board<T>::getminiboard(int index) {
    return miniBoards[index];
}
template <typename T>
void ultimateTTT_board<T>::display_board() {
    cout<<"  ";
    for (int j = 0; j < this->columns;j++) {
        cout<< "   " <<j <<"    ";
    }
    cout<<endl;
    for (int i = 0; i < this->rows; i++) {
        cout << "  +";
        for (int j = 0; j < this->columns; j++) {
            cout << "------+";
        }
        cout<<endl;
        // Print row number and board content
        cout << i << " | ";
        for (int j = 0; j < this->columns; j++) {
            cout << "  " << this->board[i][j] << "  | "; // Adjusted for more space
        }
        cout <<endl;
    }

    cout << "  +";
    for (int j = 0; j < this->columns;j++) {
        cout << "------+"; // Adjusted for more space
    }
    cout <<endl;
}

template <typename T>
bool ultimateTTT_board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if(this->board[x][y]=='X'||this->board[x][y]=='O'||this->board[x][y]=='-') {
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
template <typename T>
void ultimateTTT_player<T>::getmove(int& x, int& y) {

    // Store the original board pointer
    Board<T>* originalBoardPtr=this->boardPtr;

    int newboard;
    cout <<"Please choose which mini board (0,8): ";
    cin >>newboard;
    ultimateTTT_board<T>* ultimateBoardPtr = dynamic_cast<ultimateTTT_board<T>*>(this->boardPtr);//to use the derived class methods
    this->boardPtr = &ultimateBoardPtr->getminiboard(newboard); // now points to the miniboard selected by the user
    while(this->boardPtr->is_win()||this->boardPtr->is_draw()) { //checker to prevent user to play on a miniboard that has a winner
        cout<<"This board already has a winner! "<<endl;
        cout << "Please choose which mini board (0,8): ";
        cin >> newboard;
        this->boardPtr = &ultimateBoardPtr->getminiboard(newboard);
    }
    this->boardPtr->display_board();
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    if(ultimateBoardPtr->counter%2==0) { //second player move
        this->boardPtr->update_board(x,y,'O');
    }else if (ultimateBoardPtr->counter%2!=0) { //first player move
        this->boardPtr->update_board(x,y,'X');
    }
    ultimateBoardPtr->display_allboards(); //display all board for the user

    if (this->boardPtr->is_win()) {
        if(ultimateBoardPtr->counter%2==0) { //if second player won the miniboard then its symbol updates on the main board
            originalBoardPtr->update_board(newboard/3,newboard%3,'O');
            // ultimateBoardPtr->counter--;
        }else if (ultimateBoardPtr->counter%2!=0) { //if first player won the miniboard then its symbol updates on the main board
            originalBoardPtr->update_board(newboard/3,newboard%3,'X');
            ultimateBoardPtr->counter--;
        }
    }
    if (this->boardPtr->is_draw()) { //if it is draw then the symbol - appears on the main board
        originalBoardPtr->update_board(newboard/3,newboard%3,'-');
    }

    this->boardPtr = originalBoardPtr; //resets the pointer to the main board again
    this->symbol=0; //to update the main board with nothing
    cout<<"Displaying main Board: "<<endl;
}

template <typename T>
bool ultimateTTT_board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }
    return false;
}
template <typename T>
bool ultimateTTT_board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}
template <typename T>
bool ultimateTTT_board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
ultimateTTT_randomplayer<T>::ultimateTTT_randomplayer(T symbol, Board<T>* board) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    this->boardPtr = board;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void ultimateTTT_randomplayer<T>::getmove(int& x, int& y) {
    // Store the original board pointer
    Board<T>* originalBoardPtr =this->boardPtr;
    int newboard = rand() % 9; //choose a random number 0-8
    ultimateTTT_board<T>* ultimateBoardPtr = dynamic_cast<ultimateTTT_board<T>*>(this->boardPtr);
    if (ultimateBoardPtr) {
        this->boardPtr =&ultimateBoardPtr->getminiboard(newboard); // now points to the miniboard selected by the random player
        while(this->boardPtr->is_win()||this->boardPtr->is_draw()) { //checker to prevent playing on finished boards
            newboard=rand() %9;
            this->boardPtr = &ultimateBoardPtr->getminiboard(newboard);
        }
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        if(ultimateBoardPtr->counter%2==0) {
            this->boardPtr->update_board(x,y,'O');
        }else if (ultimateBoardPtr->counter%2!=0) {
            this->boardPtr->update_board(x,y,'X');
        }
        ultimateBoardPtr->display_allboards();
        if (this->boardPtr->is_win()) { //update the board incase there is a winner on the mini board
            if(ultimateBoardPtr->counter%2==0) {
                originalBoardPtr->update_board(newboard/3,newboard%3,'O');
                // ultimateBoardPtr->counter--;
            }else if (ultimateBoardPtr->counter%2!=0) {
                originalBoardPtr->update_board(newboard/3,newboard%3,'X');
                ultimateBoardPtr->counter--;
            }
        }
        if (this->boardPtr->is_draw()) {
            originalBoardPtr->update_board(newboard/3,newboard%3,'-');
        }
        this->boardPtr = originalBoardPtr;
        this->symbol=0;
        cout<<"Displaying main Board: "<<endl;
    } else {
        cout << "Error: Invalid board pointer type." << endl;
    }
}
template <typename T>
ultimateTTT_player<T>::ultimateTTT_player(string name, T symbol, Board<T>* board) : Player<T>(name, symbol) {
    this->boardPtr = board;
}

//#include "BoardGame_Classes.h"


template <typename T>
class misere_Board:public Board<T>          //misere board class
{
public:
    int win = 0;
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    void assign_move(int &x, int &y);
    bool is_win() ;
    bool is_draw();
    bool getWin();
    bool game_is_over();
    misere_Board();
};

template <typename T>
class misere_Player: public Player<T>
{
    void getmove(int& x, int& y) ;
    misere_Board<T>*brd;
public:
    misere_Player(string name, T symbol, misere_Board<T>* board);
};

template <typename T>
class misere_Random_Player : public RandomPlayer<T>{
public:
    misere_Random_Player(T symbol);
    void getmove(int &x, int &y) ;
};



//---------------------Implementation

// Constructor for misere_Board
template <typename T>
misere_Board<T>::misere_Board() {
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
bool misere_Board<T>::update_board(int x, int y, T mark) {
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
void misere_Board<T>::display_board() {
    if(win)
        return;
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
bool misere_Board<T>::is_win() {

    if (win)
        return true;
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            if(!win)
            {
                win++;
                return false;
            }
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        if(!win)
        {
            win++;
            return false;
        }
        //current player lost
    }

    return false;
}




// Return true if 9 moves are done and no winner
template <typename T>
bool misere_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool misere_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
bool misere_Board<T>::getWin()
{
    return win;
}

template <typename T>
void misere_Board<T>::assign_move(int &x, int &y) {
    for (int i = 0; i < this->rows; i++){
        for(int j = 0; j<this->columns; j++){
            if(this->board[i][j] == '\0'){
                x = i;
                y = j;
                return;
            }
        }
    }
}


// Constructor for misere_Player
template <typename T>
misere_Player<T>::misere_Player(string name, T symbol, misere_Board<T>* board) : Player<T>(name, symbol) {brd = board;}

template <typename T>
void misere_Player<T>::getmove(int& x, int& y) {
    if(brd->getWin())
    {
        brd->assign_move(x,y);
        return;
    }

    cout << endl<<this->name <<"'s turn";
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for misere_Random_Player
template <typename T>
misere_Random_Player<T>::misere_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void misere_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}



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

template <typename T>
class inarow_Board:public Board<T> {
public:
    inarow_Board ();
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
class inarow_Player : public Player<T> {
private:
    inarow_Board<T>& board;
public:
    inarow_Player (string name, T symbol,inarow_Board<T>& b);
    void getmove(int& x, int& y) ;

};

template <typename T>
class inarow_Random_Player : public RandomPlayer<T>{
public:
    inarow_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for inarow_Board
template <typename T>
inarow_Board<T>::inarow_Board() {
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
bool inarow_Board<T>::update_board(int x, int y, T mark) {
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
void inarow_Board<T>::display_board() {
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
bool inarow_Board<T>::is_win() {
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
bool inarow_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool inarow_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for inarow_Player
template <typename T>
inarow_Player<T>::inarow_Player(string name, T symbol, inarow_Board<T>& b)
        : Player<T>(name, symbol), board(b) {}

template <typename T>
void inarow_Player<T>::getmove(int& x, int& y) {
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

// Constructor for inarow_Random_Player
template <typename T>
inarow_Random_Player<T>::inarow_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void inarow_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 6;  // Random number between 0 and 5
    y = rand() % this->dimension; // random number between 0 and 6
}



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

#include <set>
template <typename T>
class Numerical_Board:public Board<T> {
public:
    Numerical_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    static int n_moves;
    static set<int> availableNumbers;


};
template <typename T>
int Numerical_Board<T>::n_moves = 0;
template <typename T>
set<int> Numerical_Board<T>::availableNumbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

template <typename T>
class Numerical_Player : public Player<T> {
public:
    Numerical_Player (string name, T symbol);
    void getmove(int& x, int& y) ;



};

template <typename T>
class Numerical_Random_Player : public RandomPlayer<T>{
public:
    Numerical_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Numerical_Board
template <typename T>
Numerical_Board<T>::Numerical_Board() {
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
bool Numerical_Board<T>::update_board(int x, int y, T mark) {
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
void Numerical_Board<T>::display_board() {
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
bool Numerical_Board<T>::is_win() {
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
bool Numerical_Board<T>::is_draw() {

    int count = this->n_moves;
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Numerical_Player
template <typename T>
Numerical_Player<T>::Numerical_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Numerical_Player<T>::getmove(int& x, int& y) {

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    char num1;
    int av;
    int movecount =Numerical_Board<T>::n_moves;

    if(movecount%2==0) {
        int count=0;
        while(count!=1) {
            cout<<"enter an odd available number from (1 to 9): \n";
            cin>>av;
            if(av%2!=0 && (Numerical_Board<T>::availableNumbers.find(av) !=Numerical_Board<T>::availableNumbers.end())&& 1<=av<=9) {
                count = 1;
                Numerical_Board<T>::availableNumbers.erase(av);
            }
            else cout<<"enter another number!"<<endl;

        }
    }
    if(movecount%2!=0) {
        int count=0;
        while(count!=1) {
            cout<<"enter an even available number from (1 to 9) : \n";
            cin>>av;
            if(av%2==0 &&(Numerical_Board<T>::availableNumbers.find(av) !=Numerical_Board<T>::availableNumbers.end()) && 1<=av<=9) {
                count = 1;
                Numerical_Board<T>::availableNumbers.erase(av);
            }
            else cout<<"enter another number!"<<endl;
        }
    }

    this->symbol = av+ '0';

}

// Constructor for Numerical_Random_Player
template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    // Generate random x and y for move placement
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;

    int move = Numerical_Board<T>::n_moves;
    vector<int> evenNumbers;
    vector<int> oddnum;

    // Separate even and odd numbers from availableNumbers
    for (int num : Numerical_Board<T>::availableNumbers) {
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
        Numerical_Board<T>::availableNumbers.erase(evn);  // Remove from available numbers
    }
    else if (move % 2 == 0 && !oddnum.empty()) {
        int ind1 = rand() % oddnum.size();
        int odd = oddnum[ind1];
        this->symbol = odd + '0';  // Update the symbol with the odd number selected
        Numerical_Board<T>::availableNumbers.erase(odd);  // Remove from available numbers
    }
}


//Game 5x5_FxF

template <typename T>
class FxF_Board:public Board<T> {
    int win = 0;
public:
    FxF_Board ();
    ~FxF_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    int getMoves ()
    {return this->n_moves;}
    void assign_move(int &x, int &y) {
        for (int i = 0; i < this->rows; i++){
            for(int j = 0; j<this->columns; j++){
                if(this->board[i][j] == '\0'){
                    x = i;
                    y = j;
                    return;
                }
            }
        }
    }
    int counter(T symbol);  //to count number of three longs per symbol
    //TODO int who_won();          //to test and see who won, returns number referring to index of player in the players[] array -> X is 0, O is 1

};

template <typename T>
class FxF_manager:public GameManager<T>
{
public:
    void run();
};

template <typename T>
class FxF_Player : public Player<T> {
private:

public:
    FxF_Board<T>* boardPtr;
    FxF_Player (string name, T symbol, FxF_Board<T>* board);

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
FxF_Board<T>::FxF_Board(){          //constructor for board
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
FxF_Board<T>::~FxF_Board(){         //Destructor for board for cleaning memory
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
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
    if(this->n_moves == 25)
        return;

    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << "  " << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------------------------";
    }
    cout << endl;
}

template <typename T> bool FxF_Board<T>::is_win()
{   int cs1 = counter('X');
    int cs2 = counter('O');
    //cout << "Player 1 Score: "<< cs1 << "  Player 2 Score: " << cs2 << endl;
    if (win && this->n_moves == 25)  {
        return true;
    }

    if ((cs1 != cs2) && this->n_moves == 24) {
        if (cs2 > cs1) {
            return true;
        }
        else {
            win++;
            return false;
        }
    }
    else {
        return false;
    }
}



template <typename T> bool FxF_Board<T>::is_draw()
{
    return (this->n_moves >= 25 && !is_win());
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
FxF_Player<T>::FxF_Player(string name, T symbol, FxF_Board<T>*board) : Player<T>(name, symbol) {board = boardPtr;}

template <typename T>
void FxF_Player<T>::getmove(int& x, int& y) {
    if(boardPtr -> getMoves() == 24)
    {
        boardPtr -> assign_move(x, y);
    }
    else
    {
        cout << this->name << "'s turn. Enter move (0 - 4), two numbers seperated by space: ";
        cin >> x >> y;
    }
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




#endif //A2_GAMES_H
