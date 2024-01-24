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

string encryptRailFenceCipher(const string& text, int rails) { //Шифр Железнодорожной изгороди
    string result = "";
    int textLength = text.length();
    int cycleLength = 2 * (rails - 1);

    for (int i = 0; i < rails; ++i) {
        for (int j = i; j < textLength; j += cycleLength) {
            result += text[j];
            if (i > 0 && i < rails - 1 && j + cycleLength - 2 * i < textLength) {
                result += text[j + cycleLength - 2 * i];
            }
        }
    }

    return result;
}

string decryptRailFenceCipher(const string& text, int rails) { //дешифр Железнодорожной изгороди
    string result(text.length(), ' ');
    int textLength = text.length();
    int cycleLength = 2 * (rails - 1);
    int railIndex = 0;

    for (int i = 0; i < textLength; ++i) {
        result[i] = text[railIndex];

        if (railIndex == 0 || railIndex == rails - 1) {
            railIndex += cycleLength;
        } else {
            if (i % cycleLength < rails - 1) {
                railIndex += cycleLength - 2 * (i % cycleLength);
            } else {
                railIndex += 2 * (i % cycleLength) - cycleLength;
            }
        }
    }

    return result;
}

// Подготовка ключа: приведение к верхнему регистру и замена 'J' на 'I' для шифра ключевого квадрата
string preparePlayfairKey(const string& key) {
    string preparedKey = key;
    for (char& c : preparedKey) {
        c = toupper(c);
        if (!isalpha(c) || c == 'J') {
            c = 'I';
        }
    }
    return preparedKey;
}

// Генерация матрицы для шифра ключевого квадрата
void generatePlayfairMatrix(const string& key, char matrix[5][5]) {
    string preparedKey = preparePlayfairKey(key);
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    int k = 0;
    for (char c : preparedKey + alphabet) {
        if (preparedKey.find(c) == string::npos) {
            matrix[k / 5][k % 5] = c;
            k++;
        }
    }
}

// Поиск координат символа в матрице для шифра ключевого квадрата
void findPlayfairCoordinates(char matrix[5][5], char c, int& row, int& col) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

// Шифрование шифром ключевого квадрата
string encryptPlayfairCipher(const string& text, const string& key) {
    char matrix[5][5];
    generatePlayfairMatrix(key, matrix);

    string result = "";
    int textLength = text.length();

    for (int i = 0; i < textLength; i += 2) {
        char firstChar = text[i];
        char secondChar = (i + 1 < textLength) ? text[i + 1] : 'X';

        int firstRow, firstCol, secondRow, secondCol;
        findPlayfairCoordinates(matrix, firstChar, firstRow, firstCol);
        findPlayfairCoordinates(matrix, secondChar, secondRow, secondCol);

        if (firstRow == secondRow) {
            result += matrix[firstRow][(firstCol + 1) % 5];
            result += matrix[secondRow][(secondCol + 1) % 5];
        } else if (firstCol == secondCol) {
            result += matrix[(firstRow + 1) % 5][firstCol];
            result += matrix[(secondRow + 1) % 5][secondCol];
        } else {
            result += matrix[firstRow][secondCol];
            result += matrix[secondRow][firstCol];
        }
    }

    return result;
}

// Дешифрование шифром ключевого квадрата
string decryptPlayfairCipher(const string& text, const string& key) {
    char matrix[5][5];
    generatePlayfairMatrix(key, matrix);

    string result = "";
    int textLength = text.length();

    for (int i = 0; i < textLength; i += 2) {
        char firstChar = text[i];
        char secondChar = (i + 1 < textLength) ? text[i + 1] : 'X';

        int firstRow, firstCol, secondRow, secondCol;
        findPlayfairCoordinates(matrix, firstChar, firstRow, firstCol);
        findPlayfairCoordinates(matrix, secondChar, secondRow, secondCol);

        if (firstRow == secondRow) {
            result += matrix[firstRow][(firstCol + 4) % 5];
            result += matrix[secondRow][(secondCol + 4) % 5];
        } else if (firstCol == secondCol) {
            result += matrix[(firstRow + 4) % 5][firstCol];
            result += matrix[(secondRow + 4) % 5][secondCol];
        } else {
            result += matrix[firstRow][secondCol];
            result += matrix[secondRow][firstCol];
        }
    }

    return result;
}

void printMainMenu(){
    cout << "\033[2J\033[1;1H";
    cout << "ШИФРОВКА/ДЕШИФРОВКА" << endl;
    cout << "1 = Шифр Цезаря" << endl;
    cout << "2 = Шифр Виженера" << endl;
    cout << "3 = Атбаш" << endl;
    cout << "4 = Шифр ограждения рельсов" << endl;
    cout << "5 = Шифр Плейфера" << endl;
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
        else if (input == "4"){
            while (true) {
                printCipherMenu("ШИФР ОГРАЖДЕНИЯ РЕЛЬСОВ");
                cout << "Выберите вариант: ";
                getline(cin, input);

                if (input == "0"){
                    input = " ";
                    break;
                }
                else if (input == "1"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ШИФРОВКА" << endl;
                    cout << "Введите кол-во рельсов: ";
                    cin >> rails;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Шифрованное слово: " << encryptRailFenceCipher(word, rails) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
                else if (input == "2"){
                    cout << "\033[2J\033[1;1H";
                    cout << "ДЕШИФРОВКА" << endl;
                    cout << "Введите кол-во рельсов: ";
                    cin >> rails;
                    cout << "Введите слово: ";
                    cin >> word;
                    cout << "Дешифрованное слово: " << decryptRailFenceCipher(word, rails) << endl;
                    cout << "Введите любую букву: ";
                    cin >> word;
                }
            }
        }
        else if (input == "5"){
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
        else{
            printMainMenu();
            cout << "Выберите шифр: ";
            getline(cin, input);
        }
    }
}