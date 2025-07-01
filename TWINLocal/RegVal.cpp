#include "RegVal.h"
#include <windows.h>
#include <iostream>

void setUpRegVal() //better names, auto runs
{
	HKEY hKey = NULL;
	const char* regValueForStartup = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LPCWSTR lpSubKey = reinterpret_cast<LPCWSTR>(regValueForStartup);
	DWORD ulOptions = 0;
	REGSAM samDesired = 0;
	PHKEY phkResult = NULL;
	LONG regKey = RegOpenKeyEx(NULL, lpSubKey, ulOptions, samDesired, phkResult);

	if (regKey != ERROR_SUCCESS)
	{
		if (regKey == ERROR_FILE_NOT_FOUND) {
			printf("Key not found.\n");
		}
		else {
			printf("Error opening key. %d\n", regKey);
			//const DWORD size = 100 + 1;
			///WCHAR buffer[size];
			//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, reinterpret_cast<LPCVOID>(regKey), 0, 0, buffer, NULL, NULL);
			//std::cout << buffer;
		}
	}


	LPCWSTR lpValueName = reinterpret_cast<LPCWSTR>("C:\\Users\\roini\\source\\repos\\TWINLocal\\Debug\\TWINLocal.exe");
	DWORD Reserved = 0;
	DWORD dwType = REG_SZ;
	const BYTE* lpData = NULL;
	DWORD cbData = sizeof(lpData);
	LONG setRegKey = RegSetValueEx(*phkResult, lpValueName, Reserved, dwType, lpData, cbData);
}
