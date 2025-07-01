#include "DisplayBox.h"
#include "RegVal.h"
#include "Mutex.h"

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
    DisplayResourceNAMessageBox();

    //new way to close handle

    return 0;
}