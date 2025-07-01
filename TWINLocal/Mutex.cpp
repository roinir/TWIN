#include "Mutex.h"

Mutex::Mutex() {
	m_ghMutex = CreateMutex(
        NULL,                        // default security descriptor
        FALSE,                       // mutex not owned
        TEXT("NameOfMutexObject"));  // object name
}


Mutex::~Mutex()
{
    CloseHandle(m_ghMutex);
}

HANDLE Mutex::getMutex() const
{
    return m_ghMutex;
}