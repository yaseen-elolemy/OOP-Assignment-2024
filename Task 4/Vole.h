#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <cmath>
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
    int hexToDecimal (int Reg,Machine& machine) {
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
        return value;
    }
    string decimalToBinary(int decimal) {
        if (decimal == 0) return "0";
        string binary = "";
        while (decimal > 0) {
            binary = to_string(decimal % 2) + binary;
            decimal /= 2;
        }
        return binary;
    }
    int BinaryToDecimal(string Binary) {
        int decimal=0;
        int base=1;
        for (int i=Binary.length()-1;i>=0;i--) {
            if (Binary[i]=='1') {
                decimal+=base;
            }
            base*=2;
        }
        return decimal;
    }
    double BinaryFractionToDecimal(string Binary,Machine& machine) {
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
    float BinaryToFloating(string Binary,Machine& machine) {
        string sign="";
        string exponent="";
        string mantissa="";
        int bias=4;
        for(int i=0;i<Binary.length();i++) {
            if(i==0) {
                sign+=Binary[i];
            }else if(i > 0 && i < 4) {
                exponent+=Binary[i];
            }else if(i > 3 && i < 8) {
                mantissa+=Binary[i];
            }
        }
        int BinaryExponent=BinaryToDecimal(exponent);
        float BinaryMantissa=BinaryFractionToDecimal(mantissa,machine);
        int BinarySign=pow(-1,stoi(sign));
        float equation=BinarySign*BinaryMantissa*pow(2,BinaryExponent-bias);
        return equation;
    }
    string decimalFractionToBinary(double fractional) {
        string binary = "";
        int limit = 20; // Limit the number of decimal places
        while (limit > 0) {
            fractional *= 2;
            if (fractional >= 1) {
                binary += "1";
                fractional -= 1;
            } else {
                if (fractional * 2 >= 1) {
                    binary += "0";
                }
            }
            limit--;
        }
        return binary;
    }
    void FloatingToBinary(int newReg,float FloatNum,Machine& machine) {
        vector<Register>& registers = machine.getRegisters();
        // vector<Memory>& memory = machine.getMemory();
        //-5.5
        int sign=0; //there is no sign
        if(FloatNum<0) {
            sign=1; //there is a negative sign
            FloatNum=FloatNum*-1; //to make the number positive
        }
        int integerPart=floor(FloatNum); //to take the integer part of the number
        float fractionalPart=FloatNum-integerPart; //to take the fractional part of the number
        int exponent=0;
        string IntegerBinary=decimalToBinary(integerPart); //to convert the integer part to binary
        string FractionalBinary=decimalFractionToBinary(fractionalPart); //to convert the fractional part to binary
        bool flag=false; //to check if the number is normalized or not
        string mantissa="";
        for(int i=0;i<IntegerBinary.size();i++) {// Normalize the integer part
            if(IntegerBinary[i]=='1') {
                exponent=IntegerBinary.size()-i;
                mantissa = IntegerBinary.substr(i ) + FractionalBinary;
                exponent+=4; //adding the exponent bias
                flag=true;
                break;
            }
        }
        if(flag==false) {// Normalize the fractional part if integer part is zero
            for(int i=0;i<FractionalBinary.size();i++) {
                if(FractionalBinary[i]=='1') {
                    exponent=-i;
                    exponent+=4; //adding the exponent bias
                    mantissa = FractionalBinary.substr(i);
                    flag=true;
                }
            }
        }
        if (mantissa.size() > 4) {
            mantissa = mantissa.substr(0, 4);
        } else {
            while (mantissa.size() < 4) {
                mantissa += "0";
            }
        }
        // cout<<sign<<' '<<exponent<<' '<<mantissa<<endl;
        string BinaryExponent=decimalToBinary(exponent);
        string FinalBinary=to_string(sign)+BinaryExponent+mantissa;
        int FinalDecimal=BinaryToDecimal(FinalBinary);
        string FinalHex=decimalToHex(FinalDecimal);
        registers[newReg].SetValue(FinalHex);
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
