#pragma once

#include <windows.h>
#include <iostream>

#include "Exception.h"

// mutex class in charge of initializing and closing the mutex handle
class Mutex
{
	public:
		/**
		* @brief constructor - initializing a mutex object
		* @throws CreateMutexError if there was a problem with creating the mutex - regardless if it was taken or not
		*/
		Mutex();

		/**
		* @brief destructor - closes the mutex handle for other processes
		*/
		~Mutex(); 

		/**
		* @brief creates a new mutex object if not already taken
		* @return 1 if it was taken and 0 if it is available
		*/
		void isMutexTaken() const;

	private:
		HANDLE m_ghMutex; //mutex handle
};

class CreateMutexException: public ExceptionClass
{
	int handleException() const override;
};

class MutexTakenException: public ExceptionClass
{
	int handleException() const override;
};
