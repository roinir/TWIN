#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#include "Server.h"
#include <string>
//#include "ExecuteFile.h"

Server::Server()
{
    printf("Initializing the server\n");
    WSADATA wsaData;

    struct addrinfo hints;


    initWinsock(&wsaData);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    resolveAddrAndPort(&hints);

    initListening();

    bindSock();

    startListening();

    acceptConnection();

    communicate();
}

void Server::initWinsock(WSADATA* wsaData)
{
    m_iResult = WSAStartup(MAKEWORD(2, 2), wsaData);
    if (m_iResult != 0) {
        throw InitSockException();
    }
}

void Server::resolveAddrAndPort(struct addrinfo* hints)
{
    int m_iResult = getaddrinfo(NULL, DEFAULT_PORT, hints, &m_result);
    if (m_iResult != 0) {
        throw GetAddrInfoException();
    }
}

void Server::initListening()
{
    printf("Server starts listening\n");
    m_ListenSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
    if (m_ListenSocket == INVALID_SOCKET) {
        throw InitListenException();
    }
}

void Server::bindSock()
{
    printf("Server binds with socket\n");
    // Setup the TCP listening socket
    m_iResult = bind(m_ListenSocket, m_result->ai_addr, (int)m_result->ai_addrlen);
    if (m_iResult == SOCKET_ERROR) {
        throw BindException();
    }
}

Server::~Server()
{
    freeaddrinfo(m_result);
    closesocket(m_ListenSocket);

    // shutdown the connection since we're done
    m_iResult = shutdown(m_ClientSocket, SD_SEND);

    // cleanup
    closesocket(m_ClientSocket);
    closesocket(m_ListenSocket);
    WSACleanup();
}

void Server::startListening()
{
    m_iResult = listen(m_ListenSocket, SOMAXCONN);
    if (m_iResult == SOCKET_ERROR) {
        throw StartListeningException();
    }
    printf("Server is listening\n");
}

void Server::acceptConnection()
{
    m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
    if (m_ClientSocket == INVALID_SOCKET) {
        throw AcceptConnectionException();
    }
    printf("Server accepted the connection\n");
}

void Server::communicate()
{
    printf("Server started communicating\n");
    int iSendResult;
    std::string recvbuf;
    char tempRecv[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    do {
        printf("Starting loop\n");
        m_iResult = recv(m_ClientSocket, tempRecv, recvbuflen, 0);
        if (m_iResult > 0) {
            printf("Bytes received: %d\n", m_iResult);

            // Echo the buffer back to the sender
            if (m_iResult < DEFAULT_BUFLEN)
            {
                tempRecv[m_iResult] = '\0';
                recvbuf = tempRecv;
                if (recvbuf.compare("Ping") == 0)
                {
                    std::string response("Pong");
                    iSendResult = send(m_ClientSocket, response.c_str(), response.size(), 0);
                    continue;
                }
                else if (recvbuf.compare("exit") == 0)
                {
                    printf("Connection closing...\n");
                    std::string response("Closing connection");
                    iSendResult = send(m_ClientSocket, response.c_str(), response.size(), 0);
                    break;
                }
                /*
                else if (recvbuf.compare("RUN") == 0)
                {
                    std::string response("Which file would you like to run?");
                    iSendResult = send(m_ClientSocket, response.c_str(), response.size(), 0);
                    m_iResult = recv(m_ClientSocket, tempRecv, recvbuflen, 0);
                    if (m_iResult < DEFAULT_BUFLEN)
                    {
                        tempRecv[m_iResult] = '\0';
                        recvbuf = tempRecv;
                        runExec(tempRecv);
                    }
                    else
                    {
                        std::string response("Couldn't run the path you submited");
                        iSendResult = send(m_ClientSocket, response.c_str(), response.size(), 0);
                    }
                    break;
                }
                */
            }
            std::string response("Unknown command");
            iSendResult = send(m_ClientSocket, response.c_str(), response.size(), 0);
            
            if (iSendResult == SOCKET_ERROR) {
                closesocket(m_ClientSocket);
                WSACleanup();
                throw SendException();
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else
        {
            throw RecvException();
        }

    } while (TRUE);
}

int InitSockException::handleException() const
{
    printf("WSAStartup failed\n");
    return initSockException;
}

int GetAddrInfoException::handleException() const
{
    printf("getaddrinfo failed\n");
    return getAddrInfoException;
}

int InitListenException::handleException() const
{
    printf("socket failed with error: %ld\n", WSAGetLastError());
    return initListenException;
}

int BindException::handleException() const
{
    printf("bind failed with error: %d\n", WSAGetLastError());
    return bindException;
}

int StartListeningException::handleException() const
{
    printf("listen failed with error: %d\n", WSAGetLastError());
    return startListeningException;
}

int AcceptConnectionException::handleException() const
{
    printf("accept failed with error: %d\n", WSAGetLastError());
    return acceptConnectionException;
}

int SendException::handleException() const
{
    printf("send failed with error: %d\n", WSAGetLastError());
    return sendException;
}

int RecvException::handleException() const
{
    printf("recv failed with error: %d\n", WSAGetLastError());
    return recvException;
}

int ShutDownException::handleException() const
{
    printf("shutdown failed with error: %d\n", WSAGetLastError());
    return shotDownException;
}