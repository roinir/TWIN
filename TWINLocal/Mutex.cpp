#include "Mutex.h"

Mutex::Mutex() : m_ghMutex(CreateMutex(NULL, FALSE, TEXT("TechnicianMutex")))
{
    // left blank intentionally
}


Mutex::~Mutex()
{
    CloseHandle(m_ghMutex);
}

BOOL Mutex::isMutexTaken() const 
{
    if (m_ghMutex == NULL)
    {
        throw CreateMutexError();
    }
    else
    {
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return TRUE;
        }
    }
    return FALSE;
}