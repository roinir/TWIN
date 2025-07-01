#include "DisplayBox.h"
#include "RegVal.h"
#include "Mutex.h"

int main(void)
{
    //setUpRegVal();

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
            printf("CreateMutex opened an existing mutex\n");
            return 1;
        }
        else
        {
            printf("CreateMutex created a new mutex.\n");
        }
    }

    DisplayResourceNAMessageBox();

    //new way to close handle

    return 0;
}