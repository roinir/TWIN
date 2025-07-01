#include "DisplayBox.h"


int DisplayResourceNAMessageBox()
{
	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)L"MANAGMENT PROGRAM IS UP",
		(LPCWSTR)L"message from technician",
		NULL
	);

	return msgboxID;
}