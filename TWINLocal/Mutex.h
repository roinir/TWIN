#pragma once

#include <windows.h>
#include <iostream>

// mutex class in charge of initializing and closing the mutex handle
class Mutex
{
	public:
		/**
		* @brief constructor - initializing a mutex object
		*/
		Mutex();

		/**
		* @brief destructor - closes the mutex handle for other processes
		*/
		~Mutex(); 

		/**
		* @brief creates a new mutex object if not already taken
		* @return 1 if it was taken and 0 if it was created successfully
		* @throws CreateMutexError if there was a problem with creating the mutex - regardless if it was taken or not
		*/
		BOOL isMutexTaken() const;

	private:
		HANDLE m_ghMutex; //mutex handle
};

class CreateMutexError
{
	// left blank intentionally
};
