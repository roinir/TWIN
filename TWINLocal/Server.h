#pragma once
#include "Exception.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


class Server
{
    public:
        
        /**
        * @brief constructor to initialize a Server object
        * @throws InitSockException, GetAddrInfoException, InitListenException, BindException, StartListeningException, AcceptConnectionException, SendException, RecvException, ShutDownException
        *         - it depends on the functions that are called in the consturctor
        */
        Server();

        /**
        * @brief destructor to close handles
        */
        ~Server();
    
    private:
        /**
        * @brief Initializes Winsock
        * @param wsaData contains information about Windows Sockets
        * @return void
        * @throws InitSockException if WSAStartup fails
        */
        void initWinsock(WSADATA* wsaData);

        /**
        * @brief Resolves the server address and port
        * @param hints pointer to a struct containing the adress info of the server
        * @return void
        * @throws GetAddrInfoException if getaddrinfo fails
        */
        void resolveAddrAndPort(struct addrinfo* hints);

        /**
        * @brief Creates a SOCKET for the server to listen for client connections.
        * @return void
        * @throws InitListenException if it initialized an invalid socket
        */
        void initListening();

        /**
        * @brief Sets up the TCP listening socket
        * @return void
        * @throws BindException if bind fails to bind the socket
        */
        void bindSock();

        struct addrinfo* m_result = NULL;

        /**
        * @brief Starts listening for connections
        * @return void
        * @throws StartListeningException if the listen function fails
        */
        void startListening();

        /**
        * @brief Accepts a client socket
        * @return void
        * @throws AcceptConnectionException if the accept function failed
        */
        void acceptConnection();

        SOCKET m_ListenSocket = INVALID_SOCKET;

        SOCKET m_ClientSocket = INVALID_SOCKET;

        /**
        * @brief Receives until the peer shuts down the connection
        * @return void
        * @throws SendException if the send function failed and RecvException if the recv function failed
        */
        void communicate();

        int m_iResult;
};

class InitSockException : ExceptionClass
{
    int handleException() const override;
};

class GetAddrInfoException : ExceptionClass
{
    int handleException() const override;
};

class InitListenException : ExceptionClass
{
    int handleException() const override;
};

class BindException : ExceptionClass
{
    int handleException() const override;
};

class StartListeningException : ExceptionClass
{
    int handleException() const override;
};

class AcceptConnectionException : ExceptionClass
{
    int handleException() const override;
};

class SendException : ExceptionClass
{
    int handleException() const override;
};

class RecvException : ExceptionClass
{
    int handleException() const override;
};

class ShutDownException : ExceptionClass
{
    int handleException() const override;
};