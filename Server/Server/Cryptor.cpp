#pragma once
#include "includes.h"

/*
* Data encryption and decryptionData encryption and decryption
* Шифр Цезаря - это довольно простой способ шифрования, где каждая буква в сообщении сдвигается на определенное количество позиций в алфавите. Например, при сдвиге на 3 позиции буква A станет D, B станет E, и так далее.
* Создание собственного алгоритма для шифра Цезаря не так уж и сложно, но требует времени и тестирования. Однако, важно помнить, что безопасность такого шифра довольно низкая, и его легко взломать, особенно если известен метод шифрования.
* Если вы решите написать свой алгоритм, помните, что для его эффективной работы лучше не публиковать его в открытом доступе, например, на GitHub. Это может помочь избежать нежелательного внимания и защитить ваше сообщение от дешифровки несанкционированными лицами.
*/

class CaesarCipher {
private:
    int shift;

public:
    CaesarCipher(int shift) : shift(shift) {}

    std::string encrypt(const std::string& plaintext) const {
        std::string ciphertext = plaintext;
        for (char& c : ciphertext) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = ((c - base + shift) % 26) + base;
            }
        }
        return ciphertext;
    }

    std::string decrypt(const std::string& ciphertext) const {
        std::string decryptedText = ciphertext;
        for (char& c : decryptedText) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = ((c - base - shift + 26) % 26) + base;
            }
        }
        return decryptedText;
    }
};

/*

*   Способ подключения напрямую 

int main() {
    CaesarCipher cipher(3); // Создание объекта шифра с сдвигом 3

    std::string originalText = "Hello, World!";
    std::string encryptedText = cipher.encrypt(originalText);
    std::cout << "Encrypted: " << encryptedText << std::endl;

    std::string decryptedText = cipher.decrypt(encryptedText);
    std::cout << "Decrypted: " << decryptedText << std::endl;
    return 0;
}

*/