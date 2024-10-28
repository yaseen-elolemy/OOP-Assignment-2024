#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;
class Register {
    string value;
public:
    Register(string v):value("00"){}
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
    Memory(string v):value("00"){}
    void SetValue(string v){
        value=v;
    }
    string GetValue() {
        return value;
    }
};
class Machine {
    vector<Register> Registers;
    vector<Memory> MemorySize;
public:
    Machine() : Registers(16, Register("00")), MemorySize(256, Memory("00")) {}
    vector<Register>& getRegisters() {
        return Registers;

    }
    vector<Memory>& getMemory() {
        return MemorySize;
    }
    void SetMemoryValue(int index, string value) {
        MemorySize[index].SetValue(value);
    }
    void SetRegisterValue(int index, string value) {
        Registers[index].SetValue(value);
    }
    void loadRegisterWithValue(int reg, string value) {
        if (reg>=0&&reg<Registers.size()){
            Registers[reg].SetValue(value);
        } else {
            cout<<"Invalid register"<<endl;
        }
    }
};