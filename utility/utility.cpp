#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
string encryptCaesarCipher(const string& text, int shift) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += static_cast<char>((c - base + shift) % 26 + base);
        } else {
            result += c;
        }
    }

    return result;
}
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