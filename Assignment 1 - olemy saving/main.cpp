#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> split(string target, string delimiter)
{
    int indices[2] = {0,0};
    vector <string> pieces;
    string comparer;
    string to_add;
    for(auto i : target)
    {
        comparer = i;
        if(comparer == delimiter) {
            for (int k = indices[0]; k < indices[1]; ++k)
            {
                to_add += target[k];
            }
            pieces.push_back(to_add);
            to_add.clear();
            indices[0] = indices[1]+1;

        }
        ++indices[1];
        if(indices[1] == target.length()-1 && delimiter[0] != target[-1])
        {
            for(int k = indices[0]; k <= indices[1]; ++k)
            {
                to_add += target[k];
            }
            pieces.push_back(to_add);
        }
    }
    return pieces;
}

static void binaryPrint(int n) //prints but reverse order
{
    if(n>0)
    {
        cout << n%2;
        return binaryPrint(n/2);
    }
    else
        cout << endl;
}

static bool bears(int n)
{
    if (n > 42)
    {
        if(n % 5 == 0)
        {
            return bears(n - 42);
        }
        else if (n % 3 == 0|| n % 4 == 0 && (n % 10) * ((n % 100) / 10))
        {
            return bears(n - ((n % 10) * ((n % 100) / 10)));
        }
        else if(n % 2 == 0)
        {
            return bears(n/2);
        }
    }
    if(n == 42)
        return true;
    else
        return false;

}

int countFreq(string& pat, string& txt)
{
    int M = pat.length();
    int N = txt.length();
    int res = 0;

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        /* For current index i, check for
           pattern match */
        int j;
        for (j = 0; j < M; j++)
            if (txt[i + j] != pat[j])
                break;

        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        if (j == M) {
            res++;
        }
    }
    return res;
}

int phishingScanner(string filename)
{
    string line;
    vector<string> allReadlines;
    ifstream readFile("e:\\FCI\\Object Oriented Programming\\Assignment 1\\" + filename);
    if (!readFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return 1;
    }
    cout << "Word" << "\t\t" << "Occurence" << "\t\t" << "Points Value" <<endl;
    string commons[30] = {"amazon", "official", "bank", "security", "urgent", "alert",
                          "important", "information", "ebay", "password", "credit", "verify",
                          "confirm", "account", "bill", "immediately", "address", "telephone",
                          "ssn", "charity", "check", "secure", "personal", "confidential",
                          "atm", "warning", "fraud", "citibank", "irs", "paypal" };
    int pValue[30] = { 2, 2, 1, 1, 1, 1, 1, 2,
                       3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 3, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1};
    int final_value[30];
    for(int k = 0; k<30; ++k)
    {
        final_value[k] = pValue[k];
    }
    while(getline(readFile, line))
    {
        allReadlines.push_back(line);
    }
    int occurance[30] = {0};

    for(int i = 0; i < 30; ++i) {
        for (int j = 0; j < allReadlines.size(); ++j)
        {
           occurance[i] += countFreq(commons[i], allReadlines[j]);
           //stopped here, counted frequence and occurence of each word, waiting to do pvalue & displaying data in the end
        }
        final_value[i] += occurance[i] * pValue[i];
        cout << commons[i] << "\t\t" << occurance[i] << "\t\t" << final_value[i] <<endl << "-------------------------------------------" << endl;
    }

    return 0;

}

int main() {

    int selector, to_binarize;
    string target0, delimiter0, placeholder;

    cout << "[3] Split" <<endl<<"[6] Binary Print"<<endl<<"[9] Teddy Bear Picnic" <<endl << "[12] Word problem"<< endl <<"-> ";
    cin>>selector;
    getline(cin, placeholder);
    switch (selector)
        {   case 3:
                cout << "Enter target: ";
                getline(cin, target0);
                cout << "Enter delimiter: ";
                getline(cin, delimiter0);

                for(auto i :split(target0, delimiter0)){
                    if(!i.empty() && i != delimiter0 )
                        cout << i << endl;
                }
                break;

            case 6:
                cout << "Enter number to find binary for: ";
                cin >> to_binarize;
                cout << "n = " << to_binarize<<'\t' << "output = ";
                binaryPrint(to_binarize);
                cout << endl;
                break;

            case 9:
                int bearz;
                cout << "number for bear game: "; cin >> bearz;
                if(bears(bearz))
                    cout << "bear(" << bearz << ") is true\n";

                else
                    cout << "bear(" << bearz << ") is false\n";
                break;

            case 12: { //added braces to solve initialization compilation error
                string fname;
                cout << "Enter filename to scan: ";
                getline(cin, fname);
                phishingScanner(fname);
                break;
            }
            default:
                cout << "Error: Wrong selection"<<endl;


    }
    return 0;
}
