#include <string.h>
#include "ExecuteFile.h"

#define SUCCESSFULL_SHELL_EXECUTE 42

void runExec(LPCSTR filePath, LPCSTR parms)
{
	HINSTANCE exec = ShellExecuteA(NULL, "runas", filePath, parms, NULL, 0);
	if (reinterpret_cast<int>(exec) != SUCCESSFULL_SHELL_EXECUTE)
	{
		throw ShellExecuteException();
	}
}

int ShellExecuteException::handleException() const
{
	std::cout << "Exception displaying the window occured";
	return shellExecuteException;
}