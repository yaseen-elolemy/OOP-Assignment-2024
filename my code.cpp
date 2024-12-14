#include <iostream>
#include <new> // Include the header for std::bad_alloc
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "Word Tic Tac Toe.h"

using namespace std;

int main() {
    try {
        int choice;
        Player<char>* players[2];

        ultimateTTT_board<char>* B = new ultimateTTT_board<char>();

        string playerXName, player2Name;

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
                players[0] = new ultimateTTT_player<char>(playerXName, 'X', B);
                break;
            case 2:
                players[0] = new ultimateTTT_randomplayer<char>('X');
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
                players[1] = new ultimateTTT_player<char>(player2Name, 'O', B);
                break;
            case 2:
                players[1] = new ultimateTTT_randomplayer<char>('O');
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
    } catch (const std::bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
        return 1;
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}