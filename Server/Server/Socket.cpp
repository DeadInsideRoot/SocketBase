#pragma once
#include "includes.h"

class Socket {
private:
    WSADATA wsaData;
    SOCKET serverSocket;
    sockaddr_in serverAddr;
public:
    Socket() : serverSocket(INVALID_SOCKET), serverAddr() {
        // ������������� Winsock
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            std::cerr << "������ ������������� Winsock: " << result << std::endl;
            return;
        }

        // �������� ������ ��� ������������� �������� ����������
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "������ �������� ������: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        // ��������� ������ �������
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // ��������� ���������� �� ����� ��������� IP-�����
        serverAddr.sin_port = htons(12345); // ���� ��� �������������

        // �������� ������ � ������ �������
        result = bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
        if (result == SOCKET_ERROR) {
            std::cerr << "������ �������� ������: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        // ������������� �������� ����������
        result = listen(serverSocket, SOMAXCONN); // SOMAXCONN - ������������ ���������� ��������� ����������
        if (result == SOCKET_ERROR) {
            std::cerr << "������ ������������� ������: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        std::cout << "������ ������� � ������� ����������..." << std::endl;

        // �������� ��������� ����������
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "������ �������� ����������: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        std::cout << "������ ���������." << std::endl;

        // �������� �������
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
    }

    ~Socket() {
        // ��� �������������, � ����������� �� ������ �������� �������������� ��������
        // ��� ������� ��������, ���� ��� ����.
    }
};