#include <iostream>
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
string decryptCaesarCipher(const string& text, int shift) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char decryptedChar = static_cast<char>((c - base - shift + 26) % 26 + base);
            result += decryptedChar;
        } else {
            result += c;
        }
    }

    return result;
}
string encryptVigenereCipher(const string& text, const string& key) {
    string result = "";
    int textLength = text.length();
    int keyLength = key.length();

    for (int i = 0; i < textLength; ++i) {
        char currentChar = text[i];

        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            char encryptedChar = static_cast<char>((currentChar + key[i % keyLength] - 2 * base) % 26 + base);
            result += encryptedChar;
        } else {
            result += currentChar;
        }
    }

    return result;
}
string decryptVigenereCipher(const string& text, const string& key) {
    string result = "";
    int textLength = text.length();
    int keyLength = key.length();

    for (int i = 0; i < textLength; ++i) {
        char currentChar = text[i];

        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            char decryptedChar = static_cast<char>((currentChar - key[i % keyLength] + 26) % 26 + base);
            result += decryptedChar;
        } else {
            result += currentChar;
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