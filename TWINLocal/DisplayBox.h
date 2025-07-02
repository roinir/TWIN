#pragma once
#include <windows.h>
#include <iostream>
#include "Exception.h"


/**
* @brief displays the message box and saves the user's click
* @throws DisplayWindowError if there is an error displaying the window
*/
void DisplayResourceNAMessageBoxW();

class DisplayWindowException: public ExceptionClass
{
	int handleException() const override;
};