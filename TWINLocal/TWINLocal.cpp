#include "DisplayBox.h"
#include "RegVal.h"
#include "Mutex.h"
#include "Exception.h"




/**
* @brief main function that runs all the logic
* @return success, creatingMutexException, mutexTakenException, creatingKeyException, openingKeyException - 0, 1, 2, 3, 4
*/
int main()
{
    // Create a mutex with no initial owner
    try
    {
        Mutex mutex = Mutex();
        mutex.isMutexTaken();

        RegVal();

        DisplayResourceNAMessageBoxW();
    }
    catch (ExceptionClass e)
    {
        return e.handleException();
    }

    return success;
}