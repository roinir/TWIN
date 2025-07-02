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



/**
* @brief main function that runs all the logic
* @return SUCCESS, ERROR_CREATING_MUTEX, MUTEX_TAKEN, ERROR_CREATING_KEY, ERROR_OPENING_KEY - 0, 1, 2, 3, 4
*/
int main(void)
{
    // Create a mutex with no initial owner
    try
    {
        Mutex mutex = Mutex();
        mutex.isMutexTaken();

        RegVal().createAndSetRegVal();

        DisplayResourceNAMessageBoxW();

        std::cout << "About to initialize the server";
        Server server = Server();
    }
    catch (ExceptionClass e)
    {
        return e.handleException();
    }

    return SUCCESS;
}