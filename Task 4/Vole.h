#ifndef MACHINE_H
#define MACHINE_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Register {
    string value; // Stores the value of the register
public:
    Register(string v); // Constructor to initialize the register with a value
    void SetValue(string v); // Sets the value of the register
    string getvalue(); // Returns the value of the register
};

class Memory {
    string value; // Stores the value of the memory cell
public:
    Memory(string v); // Constructor to initialize the memory cell with a value
    void SetValue(string v); // Sets the value of the memory cell
    string GetValue(); // Returns the value of the memory cell
};

class Machine {
    vector<Register> Registers; // Vector to store the registers
    vector<Memory> MemorySize; // Vector to store the memory cells
public:
    Machine(); // Constructor to initialize the machine
    vector<Register>& getRegisters(); // Returns a reference to the vector of registers
    vector<Memory>& getMemory(); // Returns a reference to the vector of memory cells
    void SetMemoryValue(int index, string value); // Sets the value of a memory cell at a specific index
    void SetRegisterValue(int index, string value); // Sets the value of a register at a specific index
};

class CU {
public:
    void MoveValue(int FirstReg, int SecondReg, Machine& machine); // Moves the value from the first register to the second register
    int hexToSignedInt(int Reg, Machine& machine); // Converts the hexadecimal value in the register to a signed integer
    int SignedAddition(int FirstVal, int SecondVal, Machine& machine); // Adds two signed integers and returns the result
    string decimalToHex(int sum); // Converts a decimal integer to a hexadecimal string
    int hexToDecimal(int Reg, Machine& machine); // Converts the hexadecimal value in the register to a decimal integer
    string decimalToBinary(int decimal); // Converts a decimal integer to a binary string
    string ExponentToBinary(int decimal); // Converts the exponent part of a decimal integer to a binary string
    int BinaryToDecimal(string Binary); // Converts a binary string to a decimal integer
    double BinaryFractionToDecimal(string Binary, Machine& machine); // Converts the fractional part of a binary string to a decimal double
    float BinaryToFloating(string Binary, Machine& machine); // Converts a binary string to a floating-point number
    string decimalFractionToBinary(double fractional); // Converts a decimal fractional number to a binary string
    void FloatingToBinary(int newReg, float FloatNum, Machine& machine); // Converts a floating-point number to a binary representation and stores it in a register
    void OP2(int target, string pattern, Machine& mac); // Sets the value of a register to a pattern
    int hex_to_dec(string hex); // Converts a hexadecimal string to a decimal integer
};

class Screen { // Class to handle screen operations
protected:
    vector<string> screenval; // Vector to store screen values
public:
    void addToScreen(string value); // Method to add a value to the screen
    void clearScreen(); // Method to clear the screen
    void printScreen(); // Method to print the screen
    void displayMemory(Machine& mac); // Method to display memory
    void displayRegister(Machine& mac); // Method to display registers
    void displayScreen(); // Method to display the screen
};

class CPU {
    CU controlunit; // CU object as a member of CPU
public:
    CPU(); // Constructor to initialize CU
    void executor(Machine& mac, int inc, CU& controlunit, Screen& screen); // Executes the program
    int loadFile(string filename, Machine& machine); // Loads a program from a file
};
#endif // MACHINE_H
