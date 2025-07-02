#pragma once
#include <windows.h>
#include <iostream>
#include "Exception.h"

void runExec(LPCSTR filePath, LPCSTR parms);

class ShellExecuteException : public ExceptionClass
{
	int handleException() const override;
};