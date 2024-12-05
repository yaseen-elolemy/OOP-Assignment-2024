#include <iostream>
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "olemy_games.h"

#include "misere.h"

using namespace std;

int main() {
    int big_choice;
    cout << "Choose game: \n[1] 5x5 Tic-Tac-Toe\n[2] Misere Tic-Tac-Toe\n-> ";
    cin >> big_choice;
    switch (big_choice)
    {
        case 1:
        {int choice;
            Player<char>* players[2];
            FxF_Board<char> *B = new FxF_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to olemy 5x5 Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new FxF_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new FxF_Random_Player<char>('X');
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
                    players[1] = new FxF_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new FxF_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }
            GameManager<char> fives(B, players);
            fives.run();
            delete B;
            delete players[0];
            delete players[1];
            break;}

        case 2:
        {
            int choice;
            Player<char>* players[2];
            misere_Board<char>* B = new misere_Board<char>();
            string playerXName, player2Name;

            cout << "Olemy Misere Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[1] = new misere_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[1] = new misere_Random_Player<char>('X');
                    break;
                default:
                    cerr << "Invalid choice for Player 1. Exiting the game.\n";
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
                    players[0] = new misere_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[0] = new misere_Random_Player<char>('O');
                    break;
                default:
                    cerr << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> misere_game(B, players);
            misere_game.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            break;
        }
        default:
            cerr << "Error: wrong selection, please try again..." << endl;

    }





    return 0;


}