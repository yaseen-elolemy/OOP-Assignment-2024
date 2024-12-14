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
#endif // WORD_TIC_TAC_TOE_H
