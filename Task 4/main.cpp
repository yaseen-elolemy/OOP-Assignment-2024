#include <iostream>
#include <sstream>
#include <fstream>
#include<string>
#include <vector>
#include "vole.h"
using namespace std;

int hex_to_dec(string hex)      //frequently used to convert from hex to decimal
{
    int y;
    std::stringstream stream;


    stream << hex;
    stream >> std::hex >> y;
     return y;

}

int main() {

    ifstream inputfile;
    Machine machine;
    int spaces=0;
    string filename, contents, reg_name;
    reg_name = "0123456789ABCDEF";
    string hex1 = "";
    vector<string> lines;
    cout<<"Please enter the file name: ";    //elmafroud n7ot 7etet el input di f class esmo instructions w n3ml function esmo readfile w ne3mlo declare gowa elmachine bs fokak delwa2ty aham 7aga el operations
    getline(cin, filename);  //fa shof lw hate3raf te3ml 7aga fel operations el awl w nseb el instructions ba3den
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
                index++;
                separtor="";
            }
        }
    }

    vector<Memory>& memory = machine.getMemory(); //get the memory

    cout << "Memory: " <<endl;

    for (int i = 0; i < memory.size(); i++) { //test loop to print the memory
        cout << memory[i].GetValue() << " ";
    }
    cout <<endl<< "Register view: " << endl;
    vector<Register>& registers = machine.getRegisters(); //get the registers
    for (int i = 0; i < registers.size(); i++) { //test loop to print the registers
        cout<<"register[0x" << reg_name[i] << "]: " << '\t';
        cout << registers[i].getvalue() << endl;
    }

    return 0;
}
