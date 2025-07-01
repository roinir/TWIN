#include "RegVal.h"
#include <windows.h>
#include <iostream>

void setUpRegVal() //better names, auto runs
{
	HKEY hKey;
	RegOpenCurrentUser(KEY_ALL_ACCESS, &hKey);
	const char* regValueForStartup = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LPCSTR lpSubKey = reinterpret_cast<LPCSTR>(regValueForStartup);
	DWORD ulOptions = 0;
	REGSAM samDesired = KEY_SET_VALUE;
	HKEY phkResult;
	LPSTR lpClass = NULL;
	DWORD dwOptions = REG_OPTION_VOLATILE;
	LPDWORD lpdwDisposition = LPDWORD();
	LSTATUS regCreate = RegCreateKeyExA(hKey, lpSubKey, 0, lpClass, REG_OPTION_VOLATILE, samDesired, NULL, &phkResult, lpdwDisposition);

	if (regCreate != ERROR_SUCCESS)
	{
		if (regCreate == ERROR_FILE_NOT_FOUND) {
			printf("Key not found.\n");
		}
		else {
			printf("Error opening key. %d\n", regCreate);
			//const DWORD size = 100 + 1;
			///WCHAR buffer[size];
			//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, reinterpret_cast<LPCVOID>(regKey), 0, 0, buffer, NULL, NULL);
			//std::cout << buffer;
		}
	}

	LPCSTR lpValueName = "TechnicianStartupWindow";
	DWORD dwType = REG_SZ;
	const char* pathToExe = "C:\\Users\\roini\\source\\repos\\TWINLocal\\Debug\\TWINLocal.exe";
	int count = 0;
	char nullTerminator = NULL;
	while (pathToExe[count] != nullTerminator)
	{
		count++;
	}
	const BYTE* lpData = reinterpret_cast<const BYTE*>(pathToExe);
	DWORD cbData = count; //23 or 24 with null ptr
	LSTATUS regSetVal = RegSetValueExA(phkResult, lpValueName, 0, dwType, lpData, cbData);

	if (regSetVal != ERROR_SUCCESS)
	{
		if (regSetVal == ERROR_FILE_NOT_FOUND) {
			printf("Key not found.\n");
		}
		else {
			printf("Error opening key. %d\n", regSetVal);
			//const DWORD size = 100 + 1;
			///WCHAR buffer[size];
			//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, reinterpret_cast<LPCVOID>(regKey), 0, 0, buffer, NULL, NULL);
			//std::cout << buffer;
		}
	}
}
