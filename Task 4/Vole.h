#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;

class Register {
    string value;
public:
    Register(string v):value("00"){} //to make the default value of the register 00
    void SetValue(string v) {
        value=v;
    }
    string getvalue() {
        return value;
    }
};
class Memory {
    string size;
    string value;
public:
    Memory(string v):value("00"){} //to make the default value of the memory 00
    void SetValue(string v){
        value=v;
    }
    string GetValue() {
        return value;
    }
};
class Machine { //the main class that contains the registers and the memory

    vector<Register> Registers; //vector of registers (16 registers)
    vector<Memory> MemorySize; //vector of memory (256 memory locations)
public:
    Machine() : Registers(16,Register("00")),MemorySize(256,Memory("00")) {} //constructor to declare the registers and the memory
    vector<Register>& getRegisters() {
        return Registers;

    }
    vector<Memory>& getMemory() {
        return MemorySize;
    }
    void SetMemoryValue(int index, string value) { //to set the value of a certain memory location
        MemorySize[index].SetValue(value);
    }
    void SetRegisterValue(int index, string value) { //to set the value of a certain register
        Registers[index].SetValue(value);
    }
    // void loadRegisterWithValue(int reg, string value) { //this is a test for operation number 2
    //     if (reg>=0&&reg<Registers.size()){
    //         Registers[reg].SetValue(value);
    //     } else {
    //         cout<<"Invalid register"<<endl;
    //     }
    // }
};
class CU { //control unit class that contains the operations
public:
    void MoveValue(int FirstReg,int SecondReg,Machine& machine) { //MOVE the bit pattern found in register R to register S
        vector<Register>& registers = machine.getRegisters();
        vector<Memory>& memory = machine.getMemory();
        string value=registers[FirstReg].getvalue();
        registers[SecondReg].SetValue(value);
    }
    int hexToSignedInt (int Reg,Machine& machine) {
        vector<Register>& registers = machine.getRegisters();
        vector<Memory>& memory = machine.getMemory();
        string Hex=registers[Reg].getvalue();
        int value=0;
        for (char c:Hex) {
            value = value * 16;
            if (c>='0' && c<='9') {
                value+=c-'0';
            } else if (c>='A' && c<='F') {
                value+=c -'A'+10;
            }
        }
        if (value>=128) {
            value-=256;
        }return value;
    }
    int SignedAddition(int FirstVal,int SecondVal,Machine&machine) {
        int sum=FirstVal+SecondVal;
        return sum;
    }
    string decimalToHex(int sum) {
        if (sum == 0) return "00";
        string hex = "";
        if (sum < 0) {
            sum += 256; // Adjust to positive equivalent in two's complement
        }
        while (sum > 0) {
            int remainder = sum % 16;
            if (remainder < 10) {
                hex = char(remainder + '0') + hex;
            } else {
                hex = char(remainder - 10 + 'A') + hex;
            }
            sum /= 16;
        }
        return hex;
    }
};


class Screen
{
protected:
    vector<string> screenval;
public:
    void addToScreen(string value)
    {
        screenval.push_back(value);
    }

    void clearScreen()
    {
        screenval.clear();
    }
    void printScreen()
    {
        cout << "Screen: ";
        for(auto i : screenval)
        {
            cout << endl << i;
        }
        cout <<endl;
    }
};
