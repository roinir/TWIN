#include "Server.h"

Server::Server()
{
    WSADATA wsaData;

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
    m_iResult = WSAStartup(MAKEWORD(2, 2), wsaData);
    if (m_iResult != 0) {
        throw InitSockError();
    }
}

void Server::m_resolveAddrAndPort(struct addrinfo* hints)
{
    int m_iResult = getaddrinfo(NULL, DEFAULT_PORT, hints, &m_result);
    if (m_iResult != 0) {
        WSACleanup();
        throw GetAddrInfoError();
    }
}

void Server::m_initListening()
{
    m_ListenSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
    if (m_ListenSocket == INVALID_SOCKET) {
        freeaddrinfo(m_result);
        WSACleanup();
        throw InitListenError();
    }
}

void Server::m_bindSock()
{
    // Setup the TCP listening socket
    m_iResult = bind(m_ListenSocket, m_result->ai_addr, (int)m_result->ai_addrlen);
    if (m_iResult == SOCKET_ERROR) {
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
    m_iResult = shutdown(m_ClientSocket, SD_SEND);
    if (m_iResult == SOCKET_ERROR) {
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
    m_iResult = listen(m_ListenSocket, SOMAXCONN);
    if (m_iResult == SOCKET_ERROR) {
        closesocket(m_ListenSocket);
        WSACleanup();
        throw StartListeningError();
    }
}

void Server::m_acceptConnection()
{
    m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
    if (m_ClientSocket == INVALID_SOCKET) {
        closesocket(m_ListenSocket);
        WSACleanup();
        throw AcceptConnectionError();
    }
}

void Server::m_communicate()
{
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    do {

        m_iResult = recv(m_ClientSocket, recvbuf, recvbuflen, 0);
        if (m_iResult > 0) {
            printf("Bytes received: %d\n", m_iResult);

            // Echo the buffer back to the sender
            iSendResult = send(m_ClientSocket, recvbuf, m_iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                closesocket(m_ClientSocket);
                WSACleanup();
                throw SendError();
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (m_iResult == 0)
            printf("Connection closing...\n");
        else {
            closesocket(m_ClientSocket);
            WSACleanup();
            throw RecvError();
        }

    } while (m_iResult > 0);
}