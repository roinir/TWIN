#include "DisplayBox.h"
#include "RegVal.h"
#include "Mutex.h"
#include "Server.h"



int main(void)
{
    // Create a mutex with no initial owner
    Mutex mutex = Mutex();

    if (mutex.getMutex() == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());
    }
    else
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return 1; //existing mutex
        }
    }

    setUpRegVal();
    DisplayResourceNAMessageBoxW();
    try
    {
        Server server = Server();
    }
    catch (InitSockError)
    {
        printf("WSAStartup failed\n");
        return 1;
    }
    catch (GetAddrInfoError)
    {
        printf("getaddrinfo failed\n");
        return 1;
    }
    catch (InitListenError)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        return 1;
    }
    catch (BindError)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        return 1;
    }
    catch (ShutDownError)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        return 1;
    }
    catch (StartListeningError)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        return 1;
    }
    catch (AcceptConnectionError)
    {
        printf("accept failed with error: %d\n", WSAGetLastError());
        return 1;
    }
    catch (SendError)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        return 1;
    }
    catch (RecvError)
    {
        printf("recv failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    return 0;
}