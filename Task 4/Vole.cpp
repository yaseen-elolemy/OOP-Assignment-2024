#include "Vole.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;
Register::Register(string v) : value("00") {} // Default value is "00"

void Register::SetValue(string v) {
    value = v; // Set the value of the register
}

string Register::getvalue() {
    return value; // Get the value of the register
}

Memory::Memory(string v) : value("00") {} // Default value is "00"

void Memory::SetValue(string v) {
    value = v; // Set the value of the memory cell
}

string Memory::GetValue() {
    return value; // Get the value of the memory cell
}

CPU::CPU() : controlunit() {} // Initialize CPU with control unit


Machine::Machine() : Registers(16, Register("00")), MemorySize(256, Memory("00")) {} // Initialize machine with 16 registers and 256 memory cells

vector<Register>& Machine::getRegisters() {
    return Registers; // Get the vector of registers
}

vector<Memory>& Machine::getMemory() {
    return MemorySize; // Get the vector of memory cells
}

void Machine::SetMemoryValue(int index, string value) {
    MemorySize[index].SetValue(value); // Set the value of a memory cell at a specific index
}

void Machine::SetRegisterValue(int index, string value) {
    Registers[index].SetValue(value); // Set the value of a register at a specific index
}

void CU::MoveValue(int FirstReg, int SecondReg, Machine& machine) {
    vector<Register>& registers = machine.getRegisters();
    string value = registers[FirstReg].getvalue(); // Get the value from the first register
    registers[SecondReg].SetValue(value); // Set the value to the second register
}

int CU::hexToSignedInt(int Reg, Machine& machine) {
    vector<Register>& registers = machine.getRegisters();
    string Hex = registers[Reg].getvalue();
    int value = 0;
    for (char c : Hex) {
        value = value * 16;
        if (c >= '0' && c <= '9') {
            value += c - '0'; // Convert hex digit to decimal (0-9)
        } else if (c >= 'A' && c <= 'F') {
            value += c - 'A' + 10; // Convert hex digit to decimal (A-F)
        }
    }
    if (value >= 128) {
        value -= 256; // Adjust for signed integer representation
    }
    return value;
}

int CU::SignedAddition(int FirstVal, int SecondVal, Machine& machine) { // Adds two signed integers and returns the result
    int sum = FirstVal + SecondVal;
    return sum;
}

string CU::decimalToHex(int sum) {
    if (sum == 0) return "00"; // Return "00" if the sum is zero
    string hex = "";
    if (sum < 0) {
        sum += 256; // Adjust to positive equivalent in two's complement
    }
    while (sum > 0) {
        int remainder = sum % 16; // Get the remainder when divided by 16
        if (remainder < 10) {
            hex = char(remainder + '0') + hex; // Convert remainder to character and prepend to hex string
        } else {
            hex = char(remainder - 10 + 'A') + hex; // Convert remainder to character and prepend to hex string
        }
        sum /= 16; // Divide sum by 16
    }
    return hex; // Return the hexadecimal string
}

int CU::hexToDecimal(int Reg, Machine& machine) { // Converts the hexadecimal value in the register to a decimal integer
    vector<Register>& registers = machine.getRegisters();
    string Hex = registers[Reg].getvalue();
    int value = 0;
    for (char c : Hex) {
        value = value * 16;
        if (c >= '0' && c <= '9') {
            value += c - '0'; // Convert hex digit to decimal (0-9)
        } else if (c >= 'A' && c <= 'F') {
            value += c - 'A' + 10; // Convert hex digit to decimal (A-F)
        }
    }
    return value;
}

string CU::decimalToBinary(int decimal) { //Converts a decimal integer to a binary string
    if (decimal == 0) return "0";
    string binary = "";
    while (decimal > 0) {
        binary = to_string(decimal % 2) + binary;
        decimal /= 2;
    }
    while (binary.length() < 8) {
        binary = "0" + binary;
    }
    return binary;
}

string CU::ExponentToBinary(int decimal) {
    if (decimal == 0) return "000"; // If the decimal is 0, return "000"
    string binary = "";
    while (decimal > 0) {
        binary = to_string(decimal % 2) + binary; // Convert decimal to binary
        decimal /= 2;
    }
    while (binary.length() < 3) {
        binary = "0" + binary; // Ensure the binary string is at least 3 bits long
    }
    return binary;
}

int CU::BinaryToDecimal(string Binary) { //Converts a binary string to a decimal integer
    int decimal = 0;
    int base = 1;
    for (int i = Binary.length() - 1; i >= 0; i--) {
        if (Binary[i] == '1') {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}

double CU::BinaryFractionToDecimal(string Binary, Machine& machine) { // Converts the fractional part of a binary string to a decimal double
    double decimal = 0.0;
    double base = 0.5;
    for (int i = 0; i < Binary.length(); i++) {
        if (Binary[i] == '1') {
            decimal += base;
        }
        base /= 2;
    }
    return decimal;
}

float CU::BinaryToFloating(string Binary, Machine& machine) {
    string sign = ""; // Sign bit
    string exponent = ""; // Exponent bits
    string mantissa = ""; // Mantissa bits
    int bias = 4; // Bias for the exponent
    for (int i = 0; i < Binary.length(); i++) {
        if (i == 0) {
            sign += Binary[i]; // First bit is the sign
        } else if (i > 0 && i < 4) {
            exponent += Binary[i]; // Next three bits are the exponent
        } else if (i > 3 && i < 8) {
            mantissa += Binary[i]; // Last four bits are the mantissa
        }
    }
    int BinaryExponent = BinaryToDecimal(exponent); // Convert exponent to decimal
    float BinaryMantissa = BinaryFractionToDecimal(mantissa, machine); // Convert mantissa to decimal
    int BinarySign = pow(-1, stoi(sign)); // Determine the sign
    float equation = BinarySign * BinaryMantissa * pow(2, BinaryExponent - bias); // Calculate the floating-point value
    return equation;
}

string CU::decimalFractionToBinary(double fractional) { // Converts a decimal fractional number to a binary string
    string binary = "";
    int limit = 20; // Limit the number of decimal places
    while (limit > 0) {
        fractional *= 2;
        if (fractional >= 1) {
            binary += "1";
            fractional -= 1;
        } else {
            binary += "0";
        }
        limit--;
    }
    return binary;
}

void CU::FloatingToBinary(int newReg, float FloatNum, Machine& machine) {
    vector<Register>& registers = machine.getRegisters();
    int sign = 0; // There is no sign
    if (FloatNum < 0) {
        sign = 1; // There is a negative sign
        FloatNum = FloatNum * -1; // Make the number positive
    }
    int integerPart = floor(FloatNum); // Take the integer part of the number
    float fractionalPart = FloatNum - integerPart; // Take the fractional part of the number
    int exponent = 0;
    string IntegerBinary = decimalToBinary(integerPart); // Convert the integer part to binary
    string FractionalBinary = decimalFractionToBinary(fractionalPart); // Convert the fractional part to binary
    bool flag = false; // Check if the number is normalized
    string mantissa = "";

    for (int i = 0; i < IntegerBinary.size(); i++) { // Normalize the integer part
        if (IntegerBinary[i] == '1') {
            exponent = IntegerBinary.size() - i;
            mantissa = IntegerBinary.substr(i) + FractionalBinary;
            exponent += 4; // Add the exponent bias
            flag = true;
            break;
        }
    }
    if (!flag) { // Normalize the fractional part if the integer part is zero
        for (int i = 0; i < FractionalBinary.size(); i++) {
            if (FractionalBinary[i] == '1') {
                exponent = -i;
                exponent += 4; // Add the exponent bias
                mantissa = FractionalBinary.substr(i);
                flag = true;
            }
        }
    }

    if (mantissa.size() > 4) { // Ensure the mantissa is exactly 4 bits long
        mantissa = mantissa.substr(0, 4);
    } else {
        while (mantissa.size() < 4) {
            mantissa += "0";
        }
    }

    string BinaryExponent = ExponentToBinary(exponent); // Convert the exponent to binary
    if (BinaryExponent.size() > 3) {
        BinaryExponent = BinaryExponent.substr(0, 3);
    }
    string FinalBinary = to_string(sign) + BinaryExponent + mantissa; // Combine sign, exponent, and mantissa
    int FinalDecimal = BinaryToDecimal(FinalBinary); // Convert the final binary to decimal
    string FinalHex = decimalToHex(FinalDecimal); // Convert the final decimal to hexadecimal
    registers[newReg].SetValue(FinalHex); // Set the value in the register
}

void CU::OP2(int target, string pattern, Machine& mac) {
    mac.SetRegisterValue(target, pattern);
}

int CU::hex_to_dec(string hex) { // Converts a hexadecimal string to a decimal integer
    int y;
    std::stringstream stream;
    stream << hex;
    stream >> std::hex >> y;
    return y;
}

void Screen::addToScreen(string value) { // Method to add a value to the screen
    screenval.push_back(value);
}

void Screen::clearScreen() { // Method to clear the screen
    screenval.clear();
}

void Screen::printScreen() { // Method to print the screen
    cout << "Screen: ";
    for (auto i : screenval) {
        cout << endl << i;
    }
    cout << endl;
}

void Screen::displayMemory(Machine& mac) { // Method to display memory
    vector<Memory>& memory = mac.getMemory(); // get the memory
    cout << "Memory: " << endl;
    for (int i = 0; i < memory.size(); i++) { // loop to print the memory
        cout << memory[i].GetValue() << " ";
    }
    cout << endl;
}

void Screen::displayRegister(Machine& mac) { // Method to display registers
    string reg_name = "0123456789ABCDEF";
    vector<Register>& registers = mac.getRegisters(); // get the registers
    for (int i = 0; i < registers.size(); i++) { // loop to print the registers
        cout << "register[0x" << reg_name[i] << "]: " << '\t';
        cout << registers[i].getvalue() << endl;
    }
    cout << "---------------------------------------------------------" << endl;
}

void Screen::displayScreen() { // Method to display the screen
    printScreen();
}

void CPU::executor(Machine& mac, int inc, CU& controlunit, Screen& screen) { // Executes the program
    int close = 0;
    int indd = 0;
    vector<Memory>& memory = mac.getMemory();
    vector<Register>& registers = mac.getRegisters();
    for (int i = 0; i % 2 == 0 && i < inc; i = i + 2 + indd) {
        indd = 0;
        if (memory[i].GetValue()[0] == 'B') {
            char jumpp = memory[i].GetValue()[1];
            int jumpp1 = (jumpp >= '0' && jumpp <= '9') ? jumpp - '0' : jumpp - 'A' + 10;
            vector<Register>& regs = mac.getRegisters();
            int jumpaddress = controlunit.hex_to_dec(memory[i + 1].GetValue());
            if (regs[jumpp1].getvalue() == regs[0].getvalue() || jumpp1 == 0) {
                indd = jumpaddress - i - 2;
                if (indd < 0) {
                    indd = jumpaddress - i - 2;
                }
            }
        }
        if (memory[i].GetValue()[0] == 'C' && memory[i + 1].GetValue() == "00") {
            close = 1;
        }
        if (close != 1) {
            if (memory[i].GetValue()[0] == '1') {
                vector<Memory>& mem = mac.getMemory();
                string memval = memory[controlunit.hex_to_dec(memory[i + 1].GetValue())].GetValue();
                int tar = memory[i].GetValue()[1] - '0';
                if (tar > 15)
                    tar = tar - 7;
                mac.SetRegisterValue(tar, memval);
            } else if (memory[i].GetValue()[0] == '2') {
                char first = memory[i].GetValue()[1];
                int tar = (first >= '0' && first <= '9') ? first - '0' : first - 'A' + 10;
                controlunit.OP2(tar, memory[i + 1].GetValue(), mac);
            } else if (memory[i].GetValue()[0] == '3' && memory[i + 1].GetValue() != "00") {
                int regaddress = memory[i].GetValue()[1] - '0';
                int memadd = controlunit.hex_to_dec(memory[i + 1].GetValue());
                vector<Register>& regs = mac.getRegisters();
                string regval = regs[regaddress].getvalue();
                mac.SetMemoryValue(memadd, regval);
                memory = mac.getMemory();
            } else if (memory[i].GetValue()[0] == '3' && memory[i + 1].GetValue() == "00") {
                int regaddress = memory[i].GetValue()[1] - '0';
                vector<Register>& regs = mac.getRegisters();
                string regval = regs[regaddress].getvalue();
                screen.clearScreen();
                stringstream ss;
                ss << hex << stoi(regval);
                string hexval = ss.str();
                screen.addToScreen(hexval);
            } else if (memory[i].GetValue()[0] == '4' && memory[i].GetValue()[1] == '0') {
                char FirstReg = memory[i + 1].GetValue()[0]; // Get the first register
                char SecondReg = memory[i + 1].GetValue()[1]; // Get the second register
                int First = (FirstReg >= '0' && FirstReg <= '9') ? FirstReg - '0' : FirstReg - 'A' + 10; // Convert the first register to an integer
                int Second = (SecondReg >= '0' && SecondReg <= '9') ? SecondReg - '0' : SecondReg - 'A' + 10; // Convert the second register to an integer
                controlunit.MoveValue(First, Second, mac); // Move the value from the first register to the second register
            } else if (memory[i].GetValue()[0] == '5') {
                char FirstReg = memory[i + 1].GetValue()[0]; // Get the first register
                char SecondReg = memory[i + 1].GetValue()[1]; // Get the second register
                int First = (FirstReg >= '0' && FirstReg <= '9') ? FirstReg - '0' : FirstReg - 'A' + 10; // Convert the first register to an integer
                int Second = (SecondReg >= '0' && SecondReg <= '9') ? SecondReg - '0' : SecondReg - 'A' + 10; // Convert the second register to an integer
                int FirstVal = controlunit.hexToSignedInt(First, mac); // Convert the hexadecimal value in the first register to a signed integer
                int SecondVal = controlunit.hexToSignedInt(Second, mac); // Convert the hexadecimal value in the second register to a signed integer
                int sum = controlunit.SignedAddition(FirstVal, SecondVal, mac); // Add the two signed integers and return the result
                string NewVal = controlunit.decimalToHex(sum); // Convert the decimal integer to a hexadecimal string
                if (NewVal.size() == 1) {
                    NewVal = "0" + NewVal;
                }
                char NewRegister = memory[i].GetValue()[1]; // Get the new register
                int NewReg = (NewRegister >= '0' && NewRegister <= '9') ? NewRegister - '0' : NewRegister - 'A' + 10; // Convert the new register to an integer
                registers[NewReg].SetValue(NewVal); // Set the value of the new register
            } else if (memory[i].GetValue()[0] == '6') {
                char FirstReg = memory[i + 1].GetValue()[0]; // Get the first register
                char SecondReg = memory[i + 1].GetValue()[1]; // Get the second register
                int First = (FirstReg >= '0' && FirstReg <= '9') ? FirstReg - '0' : FirstReg - 'A' + 10; // Convert the first register to an integer
                int Second = (SecondReg >= '0' && SecondReg <= '9') ? SecondReg - '0' : SecondReg - 'A' + 10; // Convert the second register to an integer
                int FirstDec = controlunit.hexToDecimal(First, mac); // Convert the hexadecimal value in the first register to a decimal integer
                int SecondDec = controlunit.hexToDecimal(Second, mac); // Convert the hexadecimal value in the second register to a decimal integer
                string FirstBin = controlunit.decimalToBinary(FirstDec); // Convert the decimal integer to a binary string
                string SecondBin = controlunit.decimalToBinary(SecondDec); // Convert the decimal integer to a binary string
                float FirstFloat = controlunit.BinaryToFloating(FirstBin, mac); // Convert the binary string to a floating-point number
                float SecondFloat = controlunit.BinaryToFloating(SecondBin, mac); // Convert the binary string to a floating-point number
                float sum = FirstFloat + SecondFloat; // Add the two floating-point numbers
                char NewRegister = memory[i].GetValue()[1]; // Get the new register
                int NewReg = (NewRegister >= '0' && NewRegister <= '9') ? NewRegister - '0' : NewRegister - 'A' + 10; // Convert the new register to an integer
                controlunit.FloatingToBinary(NewReg, sum, mac); // Convert the floating-point number to a binary representation and store it in the new register
            }
        }
    }
    cout << "Program executed successfully" << endl;
}

int CPU::loadFile(string filename, Machine& machine) {
    ifstream inputfile; // File stream for input file
    int inc = 0; // Instruction count
    string contents; // Variable to store file contents
    int spaces = 0; // Counter for spaces in input
    string hex1 = ""; // Temporary string for hex values
    vector<string> lines; // Vector to store lines from file
    inputfile.open(filename, ios::in); // Open the file
    if (!inputfile.is_open()) {
        cout << "File does not exist" << endl; // Error message if file does not exist
    }
    if (inputfile.is_open()) {
        cout << "File is opened!" << endl; // Message if file is successfully opened
    }
    while (getline(inputfile, contents)) { // Read file line by line
        for (int i = 0; i < contents.length(); i++) {
            if (contents[i] == ' ') {
                spaces++; // Increment space counter
            }
            if (contents[i] == 'x') {
                hex1 += contents[i + 1]; // Add hex value after 'x'
            }
            if (contents[i] == 'x' && spaces == 2) {
                hex1 += contents[i + 2]; // Add second hex value after 'x'
                spaces = 0; // Reset space counter
            }
        }
        lines.push_back(hex1); // Add hex value to lines vector
        hex1 = ""; // Reset hex1 string
    }
    int index = 0; // Memory index
    for (int i = 0; i < lines.size(); i++) {
        string separtor = ""; // Temporary string for hex pairs
        int counter = 0; // Counter for hex pairs
        for (char c : lines[i]) {
            separtor += c; // Add character to separator
            counter++;
            if (counter == 2) {
                counter = 0; // Reset counter
                machine.SetMemoryValue(index, separtor); // Set memory value
                ++inc; // Increment instruction count
                index++; // Increment memory index
                separtor = ""; // Reset separator
            }
        }
    }
    return inc; // Return instruction count
}