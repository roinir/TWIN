#include <iostream>
#include "DisplayBox.h"
#include "RegVal.h"
#include "Mutex.h"
#include "Server.h"

#define SUCCESS 0
#define ERROR_CREATING_MUTEX 1
#define MUTEX_TAKEN 2
#define ERROR_CREATING_KEY 3
#define ERROR_OPENING_KEY 4
#define INIT_SOCK_ERROR 5
#define GET_ADDR_INFO_ERROR 6
#define INIT_LISTEN_ERROR 7
#define BIND_ERROR 8
#define SHUT_DOWN_ERROR 9
#define START_LISTENING_ERROR 10
#define ACCEPT_CONNECTION_ERROR 11
#define SEND_ERROR 12
#define RECV_ERROR 13

/**
* @brief main function that runs all the logic
* @return SUCCESS, ERROR_CREATING_MUTEX, MUTEX_TAKEN, ERROR_CREATING_KEY, ERROR_OPENING_KEY, INIT_SOCK_ERROR, GET_ADDR_INFO_ERROR, 
          INIT_LISTEN_ERROR, BIND_ERROR, SHUT_DOWN_ERROR, START_LISTENING_ERROR, ACCEPT_CONNECTION_ERROR, SEND_ERROR, RECV_ERROR
                                                                                    - 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13
*/
int main(void)
{
    // Create a mutex with no initial owner
    Mutex mutex = Mutex();

    try
    {
        BOOL isTaken = mutex.isMutexTaken();
        if (isTaken)
        {
            return MUTEX_TAKEN;
        }
    }
    catch (CreateMutexError)
    {
        std::cout << "CreateMutex error: " << GetLastError() << "\n";
        return ERROR_CREATING_MUTEX;
    }

    try
    {
        RegVal().createAndSetRegVal();
    }
    catch (ErrorOpeningKey)
    {
        std::cout << "Error opening key.\n";
        return ERROR_OPENING_KEY;
    }
    catch (ErrorFindingKey)
    {
        std::cout << "Key not found.\n";
        return ERROR_CREATING_KEY;
    }


    DisplayResourceNAMessageBoxW();

    try
    {
        Server server = Server();
    }
    catch (InitSockError)
    {
        printf("WSAStartup failed\n");
        return INIT_SOCK_ERROR;
    }
    catch (GetAddrInfoError)
    {
        printf("getaddrinfo failed\n");
        return GET_ADDR_INFO_ERROR;
    }
    catch (InitListenError)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        return INIT_LISTEN_ERROR;
    }
    catch (BindError)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        return BIND_ERROR;
    }
    catch (ShutDownError)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        return SHUT_DOWN_ERROR;
    }
    catch (StartListeningError)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        return START_LISTENING_ERROR;
    }
    catch (AcceptConnectionError)
    {
        printf("accept failed with error: %d\n", WSAGetLastError());
        return ACCEPT_CONNECTION_ERROR;
    }
    catch (SendError)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        return SEND_ERROR;
    }
    catch (RecvError)
    {
        printf("recv failed with error: %d\n", WSAGetLastError());
        return RECV_ERROR;
    }


    return SUCCESS;
}