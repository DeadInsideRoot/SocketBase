#pragma once
#include "includes.h"

class Socket {
private:
    WSADATA wsaData;
    SOCKET serverSocket;
    sockaddr_in serverAddr;
public:
    Socket() : serverSocket(INVALID_SOCKET), serverAddr() {
        // Инициализация Winsock
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            std::cerr << "Ошибка инициализации Winsock: " << result << std::endl;
            return;
        }

        // Создание сокета для прослушивания входящих соединений
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка создания сокета: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return;
        }

        // Настройка адреса сервера
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Принимать соединения на любой доступный IP-адрес
        serverAddr.sin_port = htons(12345); // Порт для прослушивания

        // Привязка сокета к адресу сервера
        result = bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr));
        if (result == SOCKET_ERROR) {
            std::cerr << "Ошибка привязки сокета: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        // Прослушивание входящих соединений
        result = listen(serverSocket, SOMAXCONN); // SOMAXCONN - максимальное количество ожидающих соединений
        if (result == SOCKET_ERROR) {
            std::cerr << "Ошибка прослушивания сокета: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        std::cout << "Сервер запущен и ожидает соединений..." << std::endl;

        // Принятие входящего соединения
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка принятия соединения: " << WSAGetLastError() << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return;
        }

        std::cout << "Клиент подключен." << std::endl;

        // Закрытие сокетов
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();
    }

    ~Socket() {
        // При необходимости, в деструкторе вы можете добавить дополнительные действия
        // для очистки ресурсов, если они есть.
    }
};