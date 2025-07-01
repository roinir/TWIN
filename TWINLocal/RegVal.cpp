#include "RegVal.h"
#include <windows.h>
#include <iostream>

void setUpRegVal() //better names, auto runs
{
	HKEY hKey = HKEY_CURRENT_USER;
	const char* regValueForStartup = "\Software\Microsoft\Windows\CurrentVersion\Run";
	LPCSTR lpSubKey = reinterpret_cast<LPCSTR>(regValueForStartup);
	DWORD ulOptions = 0;
	REGSAM samDesired = KEY_ALL_ACCESS;
	HKEY phkResult;
	LPSTR lpClass = NULL;
	DWORD dwOptions = REG_OPTION_VOLATILE;
	LPDWORD lpdwDisposition = LPDWORD();
	LSTATUS regCreate = RegCreateKeyExA(hKey, lpSubKey, 0, lpClass, REG_OPTION_VOLATILE, samDesired, NULL, &phkResult, lpdwDisposition);
	//LONG regKey = RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, &phkResult);

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
	//const char* pathToExe = "C:\Users\roini\source\repos\TWINLocal\Debug\TWINLocal.exe";
	const char* testStr = "hello";
	const BYTE* lpData = reinterpret_cast<const BYTE*>(testStr);
	LSTATUS regSetVal = RegSetValueExA(phkResult, lpValueName, 0, dwType, lpData, sizeof(lpData));

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

	/*
	LPCWSTR lpValueName = reinterpret_cast<LPCWSTR>("C:\\Users\\roini\\source\\repos\\TWINLocal\\Debug\\TWINLocal.exe");
	DWORD Reserved = 0;
	DWORD dwType = REG_SZ;
	const BYTE* lpData = NULL;
	DWORD cbData = sizeof(lpData);
	LONG setRegKey = RegSetValueEx(*phkResult, lpValueName, Reserved, dwType, lpData, cbData); //KEY_SET_VALUE
	/*
	HKEY hKey = HKEY_CURRENT_USER;
	const char* regValueForStartup = "HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	LPCWSTR lpSubKey = reinterpret_cast<LPCWSTR>(regValueForStartup);
	DWORD ulOptions = 0;
	REGSAM samDesired = 0;
	PHKEY phkResult = NULL;
	LONG regKey = RegOpenKeyEx(NULL, lpSubKey, ulOptions, samDesired, phkResult);
	*/
}
