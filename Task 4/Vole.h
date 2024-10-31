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
        registers[FirstReg].SetValue("00");
    }
};
