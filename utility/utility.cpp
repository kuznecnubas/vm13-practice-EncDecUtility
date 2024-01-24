#include <iostream>
#include <string>
using namespace std;
string encryptCaesarCipher(const string& text, int shift) {//шифр цезаря
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

string decryptCaesarCipher(const string& text, int shift) {//дешифр цезаря
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

string encryptVigenereCipher(const string& text, const string& key) {//шифр виженера
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

string decryptVigenereCipher(const string& text, const string& key) { //дешифр виженера
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

string encryptAtbashCipher(const string& text) {// Шифр Атбаш
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char encryptedChar = static_cast<char>('Z' - (c - base));
            result += encryptedChar;
        } else {
            result += c;
        }
    }

    return result;
}

string decryptAtbashCipher(const string& text) {
    // Шифр Атбаш - самодекодирующийся, поэтому дешифрование и шифрование идентичны
    return encryptAtbashCipher(text);
}

void printMainMenu(){
    cout << "\033[2J\033[1;1H";
    cout << "ШИФРОВКА/ДЕШИФРОВКА" << endl;
    cout << "1 = Шифр Цезаря" << endl;
    cout << "2 = Шифр Виженера" << endl;
    cout << "3 = Атбаш" << endl;
    cout << "\n0 = Выход из программы" << endl;
}

void printCipherMenu(string cipherName){
    cout << "\033[2J\033[1;1H";
    cout << cipherName << endl;
    cout << "1 = Шифровка" << endl;
    cout << "2 = Дешифровка" << endl;
    cout << "\n0 = Выход" << endl;
}

int main(){
    system("chcp 65001");

    string input, word, key;
    int shift, rails;

    while (true){
        if (input == "0"){
            cout << "\033[2J\033[1;1H";
            cout << "Выход";
            return 0;
        }
        else if (input == "1"){
            while (true) {
                printCipherMenu("ШИФР ЦЕЗАРЯ");
                cout << "Выберите вариант: ";
                getline(cin, input);

                if (input == "0"){
                    input = " ";
                    break;
                }
                else if (input == "1"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ШИФРОВКА" << endl;
                    cout << "Введите сдвиг: ";
                    cin >> shift;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Шифрованное слово: " << encryptCaesarCipher(word, shift) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
                else if (input == "2"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ДЕШИФРОВКА" << endl;
                    cout << "Введите сдвиг: ";
                    cin >> shift;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Дешифрованное слово: " << decryptCaesarCipher(word, shift) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
            }
        }
        else if (input == "2"){
            while (true) {
                printCipherMenu("ШИФР ВИЖЕНЕРА");
                cout << "Выберите вариант: ";
                getline(cin, input);

                if (input == "0"){
                    input = " ";
                    break;
                }
                else if (input == "1"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ШИФРОВКА" << endl;
                    cout << "Введите ключ: ";
                    cin >> key;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Шифрованное слово: " << encryptVigenereCipher(word, key) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
                else if (input == "2"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ДЕШИФРОВКА" << endl;
                    cout << "Введите ключ: ";
                    cin >> key;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Дешифрованное слово: " << decryptVigenereCipher(word, key) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
            }
        }
        else if (input == "3"){
            while (true) {
                printCipherMenu("АТБАШ");
                cout << "Выберите вариант: ";
                getline(cin, input);

                if (input == "0"){
                    input = " ";
                    break;
                }
                else if (input == "1"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ШИФРОВКА" << endl;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Шифрованное слово: " << encryptAtbashCipher(word) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
                else if (input == "2"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ДЕШИФРОВКА" << endl;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Дешифрованное слово: " << decryptAtbashCipher(word) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
            }
        }
        else{
            printMainMenu();
            cout << "Выберите шифр: ";
            getline(cin, input);
        }
    }
}