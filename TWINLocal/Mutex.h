#pragma once

#include <windows.h>
#include <iostream>

// mutex class in charge of initializing and closing the mutex handle
class Mutex
{
	public:
		Mutex(); //constructor
		~Mutex(); // destructor
		HANDLE getMutex() const; // getter for the mutex handle

	private:
		HANDLE m_ghMutex; //mutex handle
};
