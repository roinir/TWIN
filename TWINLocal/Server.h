#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


class Server
{
    public:
        // constructor
        Server();
        // destructor
        ~Server();
    
    private:
        // Initialize Winsock
        void m_initWinsock(WSADATA* wsaData);

        // Resolve the server address and port
        void m_resolveAddrAndPort(struct addrinfo* hints);

        // Create a SOCKET for the server to listen for client connections.
        void m_initListening();

        // Setup the TCP listening socket
        void m_bindSock();

        struct addrinfo* m_result = NULL;

        void m_startListening();

        // Accept a client socket
        void m_acceptConnection();

        SOCKET m_ListenSocket = INVALID_SOCKET;

        SOCKET m_ClientSocket = INVALID_SOCKET;

        // Receive until the peer shuts down the connection
        void m_communicate();

        int m_iResult;
};

class InitSockError
{
    //left blank intentionally
};

class GetAddrInfoError
{
    //left blank intentionally
};

class InitListenError
{
    //left blank intentionally
};

class BindError
{
    //left blank intentionally
};

class StartListeningError
{
    //left blank intentionally
};

class AcceptConnectionError
{
    //left blank intentionally
};

class SendError
{
    //left blank intentionally
};

class RecvError
{
    //left blank intentionally
};

class ShutDownError
{
    //left blank intentionally
};