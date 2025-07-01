#include "Server.h"

Server::Server()
{
    WSADATA wsaData;
    int iResult;

    struct addrinfo hints;

    m_initWinsock(&wsaData);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    m_resolveAddrAndPort(&hints);

    m_initListening();

    m_bindSock();

    m_startListening();

    m_acceptConnection();
}

void Server::m_initWinsock(WSADATA* wsaData)
{
    int iResult = WSAStartup(MAKEWORD(2, 2), wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        throw InitSockError();
    }
}

void Server::m_resolveAddrAndPort(struct addrinfo* hints)
{
    int iResult = getaddrinfo(NULL, DEFAULT_PORT, hints, &m_result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        throw GetAddrInfoError();
    }
}

void Server::m_initListening()
{
    m_ListenSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
    if (m_ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(m_result);
        WSACleanup();
        throw InitListenError();
    }
}

void Server::m_bindSock()
{
    // Setup the TCP listening socket
    int iResult = bind(m_ListenSocket, m_result->ai_addr, (int)m_result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(m_result);
        closesocket(m_ListenSocket);
        WSACleanup();
        throw BindError();
    }
}

Server::~Server()
{
    freeaddrinfo(m_result);
    closesocket(m_ListenSocket);

    // shutdown the connection since we're done
    int iResult = shutdown(m_ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(m_ClientSocket);
        WSACleanup();
        throw ShutDownError();
    }

    // cleanup
    closesocket(m_ClientSocket);
    WSACleanup();
}

void Server::m_startListening()
{
    int iResult = listen(m_ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(m_ListenSocket);
        WSACleanup();
        throw StartListeningError();
    }
}

void Server::m_acceptConnection()
{
    m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
    if (m_ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(m_ListenSocket);
        WSACleanup();
        throw AcceptConnectionError();
    }
}

void Server::m_communicate()
{
    int iResult;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    do {

        iResult = recv(m_ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            iSendResult = send(m_ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(m_ClientSocket);
                WSACleanup();
                throw SendError();
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(m_ClientSocket);
            WSACleanup();
            throw RecvError();
        }

    } while (iResult > 0);
}