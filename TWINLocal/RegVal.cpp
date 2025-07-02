#include "RegVal.h"

#define MAX_SIZE_OF_PATH_TO_EXE 100
const std::string nameOfNewRegKey = "TechnicianStartupWindow";
const std::string pathToRegKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const std::string pathToExe = "C:\\Users\\roini\\source\\repos\\TWINLocal\\Debug\\TWINLocal.exe";



void RegVal::CreateRegKey()
{
	RegOpenCurrentUser(KEY_ALL_ACCESS, &m_currentUserKey);
	LSTATUS regCreate = RegCreateKeyExA(m_currentUserKey, reinterpret_cast<LPCSTR>(pathToRegKey.c_str()), 0, NULL, REG_OPTION_VOLATILE, KEY_SET_VALUE, NULL, &m_phkResult, LPDWORD());

	if (regCreate != ERROR_SUCCESS)
	{
		if (regCreate == ERROR_FILE_NOT_FOUND) {
			throw FileNotFoundException();
		}
		else {
			throw OpeningKeyException();
		}
	}
}

void RegVal::setRegVal()
{
	char lpExeName[MAX_SIZE_OF_PATH_TO_EXE];
	DWORD lpdwSize = MAX_SIZE_OF_PATH_TO_EXE;
	QueryFullProcessImageNameA(GetCurrentProcess(), 0, lpExeName, &lpdwSize);
	LSTATUS regSetVal = RegSetValueExA(m_phkResult, nameOfNewRegKey.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(pathToExe.c_str()), pathToExe.size());
	if (regSetVal != ERROR_SUCCESS)
	{
		if (regSetVal == ERROR_FILE_NOT_FOUND) {
			throw FindingKeyException();
		}
		else {
			throw OpeningKeyException();
		}
	}
}

RegVal::RegVal()
{
	CreateRegKey();
	setRegVal();
}

RegVal::~RegVal()
{
	RegCloseKey(m_currentUserKey);
	RegCloseKey(m_phkResult);
}


int OpeningKeyException::handleException() const
{
	std::cout << "Error opening key.\n";
	return openingKeyException;
}

int FindingKeyException::handleException() const
{
	std::cout << "Key not found.\n";
	return openingKeyException;
}

int FileNotFoundException::handleException() const
{
	std::cout << "File not found.\n";
	return fileNotFound;
}
