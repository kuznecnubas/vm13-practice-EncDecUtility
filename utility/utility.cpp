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