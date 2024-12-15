#include <iostream>
#include "BoardGame_Classes.h"

#include "games.h"

using namespace std;

int main() {
    int big_choice;
    cout <<
    "Choose game: \n[1] 5x5 Tic-Tac-Toe\n[2] Misere Tic-Tac-Toe\n[3]"
    <<" Ultimate Tic-Tac-Toe\n[4] S-U-S Tic-Tac-Toe\n[5] Four in a row Tic-Tac-Toe\n"
    <<"[6] Word Tic-Tac-Toe\n[7] Pyramid Tic-Tac-Toe\n[8] Numerical Tic-Tac-Toe\n"
    <<"-> ";
    cin >> big_choice;

    switch (big_choice) {
        case 1: {
            int choice;
            Player<char>* players[2];
            FxF_Board<char>* B = new FxF_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to olemy 5x5 Game. :)\n";

            // Set up player 1
            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    players[0] = new FxF_Player<char>(playerXName, 'X', B);
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

            switch (choice) {
                case 1:
                    players[1] = new FxF_Player<char>(player2Name, 'O', B);
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
            break;
        }

        case 2: {
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

            switch (choice) {
                case 1:
                    players[0] = new misere_Player<char>(playerXName, 'X', B);
                    break;
                case 2:
                    players[0] = new misere_Random_Player<char>('X');
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

            switch (choice) {
                case 1:
                    players[1] = new misere_Player<char>(player2Name, 'O', B);
                    break;
                case 2:
                    players[1] = new misere_Random_Player<char>('O');
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

        case 3: {
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
                        players[0] = new ultimateTTT_randomplayer<char>('X', B);
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
                        players[1] = new ultimateTTT_randomplayer<char>('O', B);
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

            break;
        }

        case 4:
        {
            int choice;
            Player<char>* players[2];
            X_O_Board<char>* B = new X_O_Board<char>();
            string playerXName, player2Name;
            char player1Letter, player2Letter;


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

            break;
        }

        case 5:
        {
            inarow_Board<char> board;

            int choice;
            Player<char>* players[2];
            inarow_Board<char>* B = new inarow_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to FCAI X-O Game. :)\n";

// Set up player 1
            cout << "Enter Player 1 name: ";
            cin >> playerXName;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new inarow_Player<char>(playerXName, 'X',board);
                    break;
                case 2:
                    players[0] = new inarow_Random_Player<char>('X');
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
                    players[1] = new inarow_Player<char>(player2Name, 'O',board);
                    break;
                case 2:
                    players[1] = new inarow_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

// Create the game manager and run the game
            GameManager<char> inarow_game(B, players);
            inarow_game.run();

// Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            break;
        }
        case 6:
        {
            int choice;
            Player<char>* players[2];
            wordTTT_Board<char>* B = new wordTTT_Board<char>();
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
                    players[0] = new wordTTT_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new wordTTT_Random_Player<char>('X');
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
                    players[1] = new wordTTT_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new wordTTT_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> WordTTT(B, players);
            WordTTT.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            break;
        }

        case 7:
        {
            int choice;
            Player<char>* players[2];
            pyramicTTT_board<char>* B = new pyramicTTT_board<char>();
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
                    players[0] = new pyramicTTT_player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new pyramicTTT_randomplayer<char>('X');
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
                    players[1] = new pyramicTTT_player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new pyramicTTT_randomplayer<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

            // Create the game manager and run the game
            GameManager<char> PyramicTTT(B, players);
            PyramicTTT.run();

            // Clean up
            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            break;
        }

        case 8:
        {
            Numerical_Board<char> board;

            int choice;
            Player<char>* players[2];
            Numerical_Board<char>* B = new Numerical_Board<char>();
            string playerXName, player2Name;

            // Set up player 1
            cout << "Enter Player 1 name: ";
            cin >> playerXName;
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new Numerical_Player<char>(playerXName, 'X');
                    break;
                case 2:
                    players[0] = new Numerical_Random_Player<char>('X');
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
                    players[1] = new Numerical_Player<char>(player2Name, 'O');
                    break;
                case 2:
                    players[1] = new Numerical_Random_Player<char>('O');
                    break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                    return 1;
            }

// Create the game manager and run the game
            GameManager<char> Numerical_game(B, players);
            Numerical_game.run();

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