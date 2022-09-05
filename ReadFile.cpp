#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    fstream myFile;
    myFile.open("silla.obj", ios::in);

    if(myFile.is_open()){
        string s;
        while(getline(myFile, s)){
            cout << s[0] << "\n";
        }
        myFile.close();
    }
}