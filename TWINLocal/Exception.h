#pragma once

enum Exceptions
{
	success = 0,
	creatingMutexException,
	mutexTakenException,
	creatingKeyException,
	openingKeyException,
	fileNotFound,
	displayWindowException,
	unknownException
};

class ExceptionClass
{
	public:
		virtual int handleException() const { return unknownException; };
};
