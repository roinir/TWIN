#include "DisplayBox.h"

int main(void)
{
    /*
    HKEY hKey = NULL;
    const char* regValueForStartup = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    LPCWSTR lpSubKey = reinterpret_cast<LPCWSTR>(regValueForStartup);
    DWORD ulOptions = 0;
    REGSAM samDesired = 0;
    PHKEY phkResult = NULL;
    LONG regKey = RegOpenKeyEx(NULL, lpSubKey, ulOptions, samDesired, phkResult);


    LPCWSTR lpValueName = reinterpret_cast<LPCWSTR>(regValueForStartup);
    DWORD Reserved = 0;
    DWORD dwType = REG_SZ;
    const BYTE* lpData = reinterpret_cast<BYTE*>("C:\\Users\\roini\\source\\repos\\TWINLocal\\Debug\\TWINLocal.exe");
    DWORD cbData = sizeof(lpData);
    LONG setRegKey = RegSetValueEx(*phkResult, lpValueName, Reserved, dwType, lpData, cbData);
    */

    // Create a mutex with no initial owner
    HANDLE ghMutex = CreateMutex(
        NULL,                        // default security descriptor
        FALSE,                       // mutex not owned
        TEXT("NameOfMutexObject"));  // object name

    if (ghMutex == NULL) 
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

    CloseHandle(ghMutex);

    return 0;
}