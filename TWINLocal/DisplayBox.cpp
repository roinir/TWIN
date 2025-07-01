#include "DisplayBox.h"


int DisplayResourceNAMessageBoxW()
{
	int msgboxID = MessageBoxW(
		NULL,
		(LPCWSTR)L"MANAGMENT PROGRAM IS UP",
		(LPCWSTR)L"message from technician",
		NULL
	);

	return msgboxID;
}