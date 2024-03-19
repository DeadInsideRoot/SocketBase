#pragma once
#include "includes.h"

/*
* Data encryption and decryptionData encryption and decryption
* ���� ������ - ��� �������� ������� ������ ����������, ��� ������ ����� � ��������� ���������� �� ������������ ���������� ������� � ��������. ��������, ��� ������ �� 3 ������� ����� A ������ D, B ������ E, � ��� �����.
* �������� ������������ ��������� ��� ����� ������ �� ��� �� � ������, �� ������� ������� � ������������. ������, ����� �������, ��� ������������ ������ ����� �������� ������, � ��� ����� ��������, �������� ���� �������� ����� ����������.
* ���� �� ������ �������� ���� ��������, �������, ��� ��� ��� ����������� ������ ����� �� ����������� ��� � �������� �������, ��������, �� GitHub. ��� ����� ������ �������� �������������� �������� � �������� ���� ��������� �� ���������� �������������������� ������.
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

*   ������ ����������� �������� 

int main() {
    CaesarCipher cipher(3); // �������� ������� ����� � ������� 3

    std::string originalText = "Hello, World!";
    std::string encryptedText = cipher.encrypt(originalText);
    std::cout << "Encrypted: " << encryptedText << std::endl;

    std::string decryptedText = cipher.decrypt(encryptedText);
    std::cout << "Decrypted: " << decryptedText << std::endl;
    return 0;
}

*/