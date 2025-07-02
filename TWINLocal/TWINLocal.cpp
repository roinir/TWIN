#include "DisplayBox.h"
#include "RegVal.h"
#include "Mutex.h"

#define SUCCESS 0
#define ERROR_CREATING_MUTEX 1
#define MUTEX_TAKEN 2
#define ERROR_CREATING_KEY 3
#define ERROR_OPENING_KEY 4

/**
* @brief main function that runs all the logic
* @return SUCCESS, ERROR_CREATING_MUTEX, MUTEX_TAKEN, ERROR_CREATING_KEY, ERROR_OPENING_KEY - 0, 1, 2, 3, 4
*/
int main()
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

    return SUCCESS;
}