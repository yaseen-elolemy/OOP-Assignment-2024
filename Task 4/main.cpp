#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include "Vole.h"
using namespace std;

int main() {
    ifstream inputfile;
    Machine machine;
    int spaces=0;
    string filename, contents;
    string hex1 = "";
    vector<string> lines;
    cout<<"Please enter the file name: ";
    getline(cin, filename);
    if(!"C:\\Users\\pc\\CLionProjects\\Task3\\"+inputfile.is_open()) {
        cout<<"File does not exist"<<endl;
    }
    inputfile.open("C:\\Users\\pc\\CLionProjects\\Task3\\"+filename,ios::in);
    while(getline(inputfile,contents)) {
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
    }for(int i=0;i<lines.size();i++) {
        cout<<lines[i]<<endl;
    }
    int index=0;
    for(int i=0;i<lines.size();i++) {
        string separtor = "";
        int counter=0;
        for(char c:lines[i]) {
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
    vector<Memory>& memorygetter = machine.getMemory();
// for(int i=0;i<256;i+=2) {                                kona ben7awel ne3ml el operation beta3et 2 bs ma3refnash
//     bool operationFound=false;
//     bool RegisterFound=false;
//     string separtor = "";
//     int counter=0;
//     for(char c:memorygetter[i].GetValue()) {
//         separtor+=c;
//         counter++;
//         operationFound=true;
//         if (counter==1&&separtor=="2") {
//
//             machine.loadRegisterWithValue(,memorygetter[i+2].GetValue());
//         }
//     }
// }
    vector<Memory>& memory = machine.getMemory();
    for (int i = 0; i < memory.size(); i++) {
        cout << memory[i].GetValue() << " ";
    }
    vector<Register>& registers = machine.getRegisters();
    for (int i = 0; i < registers.size(); i++) {
        cout<<"register: ";
        cout << registers[i].getvalue() << endl;
    }
}