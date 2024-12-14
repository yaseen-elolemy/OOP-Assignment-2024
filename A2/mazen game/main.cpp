#include <iostream>
#include "BoardGame_Classes.h"
#include "hx3X_O.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>();
    string playerXName, player2Name;
    char player1Letter, player2Letter;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "Enter your letter (S or U): ";
        cin >> player1Letter;
        players[0] = new X_O_Player<char>(playerXName, player1Letter);
        break;
        case 2:
            player1Letter = 'S';
        players[0] = new X_O_Random_Player<char>(player1Letter);
        break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
        return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "Enter your letter (S or U): ";
        cin >> player2Letter;
        players[1] = new X_O_Player<char>(player2Name, player2Letter);
        break;
        case 2:
            player2Letter = (player1Letter == 'S') ? 'U' : 'S';
        players[1] = new X_O_Random_Player<char>(player2Letter);
        break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
        return 1;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}