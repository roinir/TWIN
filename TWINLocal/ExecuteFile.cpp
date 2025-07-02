#include <string.h>
#include "ExecuteFile.h"

void runExec(LPCSTR filePath)
{
	//CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	HINSTANCE exec = ShellExecuteA(NULL, "runas", filePath, NULL, NULL, 0);
	//TODO throw exception
	//create another function that fixes string to double '\'
}

/*
LPCSTR convertToDoubleSlash(LPCSTR filePath)
{
	std::string tempPath = filePath;
	for (int i = 0; i < tempPath.size(); i++)
	{
		if (tempPath.at(i) == '\\')
		{

		}
	}
	//tempPath.replace(i, 1, "\\");
}
*/