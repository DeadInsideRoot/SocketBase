#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    setlocale(LC_ALL, "Russian");
    // ������������� Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "������ ������������� Winsock: " << result << std::endl;
        return 1;
    }

    // �������� ������ ��� �������
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "������ �������� ������: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // ��������� ������ �������
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-����� �������
    serverAddr.sin_port = htons(12345); // ���� �������

    // ����������� � �������
    result = connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "������ ����������� � �������: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "����������� � ������� �������." << std::endl;

    // �������� ������ �������
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
