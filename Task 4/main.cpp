#include <iostream>
#include <sstream>
#include <fstream>
#include<string>
#include <vector>
#include "vole.h"
using namespace std;

void OP2(int target, string pattern, Machine& mac)      //operation 2
{
    mac.SetRegisterValue(target, pattern);
}

int hex_to_dec(string hex)      //frequently used to convert from hex to decimal
{
    int y;
    std::stringstream stream;
    stream << hex;
    stream >> std::hex >> y;
    return y;

}

void executor(Machine& mac, int inc,CU& controlunit, Screen& screen)
{
    vector<Memory>& memory = mac.getMemory();
    for(int i = 0; i % 2 == 0 && i < inc; i=i+2)
    {
        if(memory[i].GetValue()[0] == '1')
        {
            vector<Memory>& mem = mac.getMemory();
            string memval = memory[hex_to_dec(memory[i+1].GetValue())].GetValue();

            int tar = memory[i].GetValue()[1] - '0';
            if(tar > 15)
                tar = tar - 7;

            mac.SetRegisterValue(tar, memval);

        }

        else if(memory[i].GetValue()[0] == '2')
        {
            int tar = memory[i].GetValue()[1] - '0';
            OP2(tar, memory[i+1].GetValue(), mac);
        }

        else if(memory[i].GetValue()[0] == '3' && memory[i+1].GetValue() != "00")
        {
            int regaddress = memory[i].GetValue()[1] - '0';
            int memadd = hex_to_dec(memory[i+1].GetValue());
            vector<Register>& regs = mac.getRegisters();
            string regval = regs[regaddress].getvalue();
            mac.SetMemoryValue(memadd, regval);
            memory = mac.getMemory();

        }

        else if(memory[i].GetValue()[0] == '3' && memory[i+1].GetValue() == "00")
        {
            int regaddress = memory[i].GetValue()[1] - '0';

            vector<Register>& regs = mac.getRegisters();
            string regval = regs[regaddress].getvalue();
            screen.addToScreen(regval);
        }

        else if(memory[i].GetValue()[0]=='4'&&memory[i].GetValue()[1]=='0') {
            // cout<<memory[i+1].GetValue()[0]<<memory[i+1].GetValue()[1]<<endl;
            controlunit.MoveValue(memory[i+1].GetValue()[0]-'0',memory[i+1].GetValue()[1]-'0',mac);
        }
    }
}



void displayScreen(Screen& screen)
{
    screen.printScreen();
}
void displayMemory(Machine& mac)
{
    vector<Memory>& memory = mac.getMemory(); //get the memory

    cout << "Memory: " <<endl;

    for (int i = 0; i < memory.size(); i++) { //test loop to print the memory
        cout << memory[i].GetValue() << " ";
    }
    cout << endl;
}
void displayRegister(Machine& mac)
{
    string reg_name;
    reg_name = "0123456789ABCDEF";
    vector<Register>& registers = mac.getRegisters(); //get the registers
    for (int i = 0; i < registers.size(); i++) { //test loop to print the registers
        cout<<"register[0x" << reg_name[i] << "]: " << '\t';
        cout << registers[i].getvalue() << endl;
    }
    cout << "---------------------------------------------------------" <<endl;
}

int loadFile(string filename, Machine& machine)
{
    ifstream inputfile;
    int inc = 0;
    string contents;
    int spaces=0;
    string hex1 = "";
    vector <string> lines;
    if(!"E:\\FCI\\Object Oriented Programming\\Task 4\\"+inputfile.is_open()) {
        cout<<"File does not exist"<<endl;
    }
    inputfile.open("E:\\FCI\\Object Oriented Programming\\Task 4\\" + filename,ios::in);
    while(getline(inputfile,contents)) {  //loop to add the contents of the file to the vector
        for(int i = 0; i < contents.length(); i++) {
            if(contents[i]==' ') {
                spaces++;
            }
            if(contents[i] == 'x') {
                hex1+=contents[i+1];
            }if(contents[i]=='x'&&spaces==2) {
                hex1+=contents[i+2];
                spaces=0;
            }
        }
        lines.push_back(hex1);
        hex1 = "";
    }
    int index=0;
    for(int i=0;i<lines.size();i++) { //loop to add each two characters to the memory (loop on the vector lines)
        string separtor = "";
        int counter=0;
        for(char c:lines[i]) { //loop on each item in the vector lines
            separtor+=c;
            counter++;
            if(counter==2) {
                counter=0;
                machine.SetMemoryValue(index,separtor);
                ++inc;
                index++;
                separtor="";
            }
        }
    }

    return inc;
}




int main() {
    int inc=0;
    Screen init;
    ifstream inputfile;
    int spaces=0;
    string filename, contents;
    Machine machine;
    CU controlunit;
    int choice=1000;
    string hex1 = "";
    vector<string> lines;
    while(choice !=0)
    {

        cout<<"[1] - Load new program from file" << endl << "[2] - Execute Program" << endl << "[3] - Display Status" << endl << "[0] - Exit Program"<<endl << "-> ";

        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "Enter file name: ";
                getline(cin, filename);
                getline(cin, filename);
                inc = loadFile( filename, machine);
                break;
            case 2:
                executor(machine, inc, controlunit, init);
                break;
            case 3:
                displayMemory(machine);
                displayRegister(machine);
                displayScreen(init);
                break;

        }


    }



    return 0;
}
