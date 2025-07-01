#include "pch.h"
#include <iostream>

HANDLE ghMutex;

DWORD WINAPI DisplayResourceNAMessageBox(LPVOID);

int main(void)
{
    HANDLE aThread;
    DWORD ThreadID;
    int i;

    // Create a mutex with no initial owner

    ghMutex = CreateMutex(
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

    if (ghMutex == NULL)
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads


    aThread = CreateThread(
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE)DisplayResourceNAMessageBox,
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier

    if (aThread == NULL)
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    // Wait for all threads to terminate

    WaitForSingleObject(aThread, INFINITE);

    // Close thread and mutex handles
    CloseHandle(aThread);

    CloseHandle(ghMutex);

    return 0;
}

int _DisplayResourceNAMessageBox()
{
    int msgboxID = MessageBox(
        NULL,
        (LPCWSTR)L"MANAGMENT PROGRAM IS UP",
        (LPCWSTR)L"message from technician",
        NULL
    );

    return msgboxID;
}

DWORD WINAPI DisplayResourceNAMessageBox(LPVOID lpParam)
{
    // Request ownership of mutex.

    DWORD dwWaitResult = WaitForSingleObject(
        ghMutex,    // handle to mutex
        INFINITE);  // no time-out interval

    switch (dwWaitResult)
    {
        // The thread got ownership of the mutex
    case WAIT_OBJECT_0:
        __try {
            _DisplayResourceNAMessageBox();
            printf("Thread %d printing the message...\n",
                GetCurrentThreadId());
        }

        __finally {
            // Release ownership of the mutex object
            if (!ReleaseMutex(ghMutex))
            {
                // Handle error.
                printf("CreateThread error: %d\n", GetLastError());
                return FALSE;
            }
        }
        break;

        // The thread got ownership of an abandoned mutex
        // The database is in an indeterminate state
    case WAIT_ABANDONED:
        return FALSE;
    }
    return TRUE;
}