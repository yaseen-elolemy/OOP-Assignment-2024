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

void executor(Machine& mac, int inc,CU& controlunit)
{
    vector<Memory>& memory = mac.getMemory();
    for(int i = 0; i % 2 == 0 || i < inc; ++i)
    {
        if(memory[i].GetValue()[0] == '2')
        {
            int tar = memory[i].GetValue()[1] - '0';
            OP2(tar, memory[i+1].GetValue(), mac);
        }
        if(memory[i].GetValue()[0]=='4'&&memory[i].GetValue()[1]=='0') {
            // cout<<memory[i+1].GetValue()[0]<<memory[i+1].GetValue()[1]<<endl;
            controlunit.MoveValue(memory[i+1].GetValue()[0]-'0',memory[i+1].GetValue()[1]-'0',mac);
        }
    }
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
    if(!"C:\\Users\\pc\\CLionProjects\\Task3\\"+inputfile.is_open()) {
        cout<<"File does not exist"<<endl;
    }
    inputfile.open("C:\\Users\\pc\\CLionProjects\\Task3\\" + filename,ios::in);
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
int hex_to_dec(string hex)      //frequently used to convert from hex to decimal
{
    int y;
    std::stringstream stream;
    stream << hex;
    stream >> std::hex >> y;
     return y;

}



int main() {
    int inc=0;
    ifstream inputfile;
    ;
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
                executor(machine, inc, controlunit);
                break;
            case 3:
                displayMemory(machine);
                displayRegister(machine);
                break;

        }


    }

    //cout<<"Please enter the file name: ";    //elmafroud n7ot 7etet el input di f class esmo instructions w n3ml function esmo readfile w ne3mlo declare gowa elmachine bs fokak delwa2ty aham 7aga el operations
    //getline(cin, filename);  //fa shof lw hate3raf te3ml 7aga fel operations el awl w nseb el instructions ba3den

    char command = ' ';
    //for(int i =0; i % 2 == 0 && i < inc; ++i)
    {

    }



    //Bellow the line is the final step which is print and displaying register and memory values

    /*vector<Memory>& memory = machine.getMemory(); //get the memory

    cout << "Memory: " <<endl;

    for (int i = 0; i < memory.size(); i++) { //test loop to print the memory
        cout << memory[i].GetValue() << " ";
    }
    cout <<endl<< "Register view: " << endl;
    vector<Register>& registers = machine.getRegisters(); //get the registers
    for (int i = 0; i < registers.size(); i++) { //test loop to print the registers
        cout<<"register[0x" << reg_name[i] << "]: " << '\t';
        cout << registers[i].getvalue() << endl;
    }*/

    return 0;
}
