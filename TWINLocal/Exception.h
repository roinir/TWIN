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
	initSockException,
	getAddrInfoException,
	initListenException,
	bindException,
	shotDownException,
	startListeningException,
	acceptConnectionException,
	sendException,
	recvException,
	shellExecuteException,
	unknownException
};

class ExceptionClass
{
	public:
		virtual int handleException() const { return unknownException; };
};
