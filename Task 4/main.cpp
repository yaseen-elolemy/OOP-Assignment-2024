#include <iostream>
#include <sstream>
#include <fstream>
#include<string>
#include <vector>
#include "vole.h"
using namespace std;

int main() {
    Machine machine; // Initialize machine
    CPU cpu; // Initialize CPU
    CU controlunit; // Initialize control unit
    Screen init; // Initialize screen
    int inc = 0; // Initialize instruction count
    ifstream inputfile; // File stream for input file
    string filename, contents; // Variables for filename and file contents
    int choice = 1000; // Variable for user choice
    string hex1 = ""; // Temporary string for hex values
    vector<string> lines; // Vector to store lines from file
    while (choice != 0) { // Loop until user chooses to exit
        cout << "[1] - Load new program from file" << endl
             << "[2] - Execute Program" << endl
             << "[3] - Display Status" << endl
             << "[4] - Display Screen" << endl
             << "[0] - Exit Program" << endl
             << "-> ";

        cin >> choice; // Get user choice
        switch (choice) {
            case 1:
                cout << "Enter file name: ";
            getline(cin, filename); // Get filename from user
            getline(cin, filename); // Read filename again to handle newline
            inc = cpu.loadFile(filename, machine); // Load file into machine
            break;
            case 2:
                cpu.executor(machine, inc, controlunit, init); // Execute program
            break;
            case 3:
                init.displayMemory(machine); // Display memory status
            init.displayRegister(machine); // Display register status
            break;
            case 4:
                init.displayScreen(); // Display screen
            break;
            case 0:
                return 0; // Exit program
            default:
                cerr << "Error: invalid input, please try again..." << endl; // Handle invalid input
            break;
        }
    }
    return 0; 
}
