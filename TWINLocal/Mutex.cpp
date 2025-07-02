#include "Mutex.h"


Mutex::Mutex() : m_ghMutex(CreateMutex(NULL, FALSE, TEXT("TechnicianMutex")))
{
    if (m_ghMutex == NULL)
    {
        throw CreateMutexException();
    }
}

Mutex::~Mutex()
{
    CloseHandle(m_ghMutex);
}

void Mutex::isMutexTaken() const 
{
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        throw MutexTakenException();
    }
}

int CreateMutexException::handleException() const
{
    std::cout << "CreateMutex error: " << GetLastError() << "\n";
    return creatingMutexException;
}

int MutexTakenException::handleException() const
{
    std::cout << "Mutex is already taken: " << GetLastError() << "\n";
    return mutexTakenException;
}