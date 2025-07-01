#pragma once

#include <windows.h>
#include <iostream>

class Mutex
{
	public:
		Mutex(); //constructor
		~Mutex(); // destructor
		HANDLE getMutex() const;

	private:
		HANDLE m_ghMutex;
};
