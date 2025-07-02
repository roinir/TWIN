#include "DisplayBox.h"


void DisplayResourceNAMessageBoxW()
{
	int msgboxID = MessageBoxW(
		NULL,
		(LPCWSTR)L"MANAGMENT PROGRAM IS UP",
		(LPCWSTR)L"message from technician",
		NULL
	);

	if (msgboxID != 1)
	{
		throw DisplayWindowException();
	}
}

int DisplayWindowException::handleException() const
{
	std::cout << "Exception displaying the window occured";
	return openingKeyException;
}