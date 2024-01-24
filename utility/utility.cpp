#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int main(){
    system("chcp 65001");
    while (true){
        string input;
        cout << "\033[2J\033[1;1H";
        cout << "ШИФРОВКА/ДЕШИФРОВКА" << endl;
        getline(cin, input);

        if (input == "0"){
            cout << "\nВыход";
            return 0;
        }
    }
}