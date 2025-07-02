#pragma once
#include <windows.h>
#include <iostream>

#include "Exception.h"


class RegVal
{
	public:
		/**
		* @brief destructor to close key handles
		*/
		~RegVal();

		/**
		* @brief used to create a key and set its value
		* @return void
		* @throws ErrorFindingKey, ErrorOpeningKey if m_CreateRegKey or m_setRegVal couldn't fund the key or open the key
		*/
		void createAndSetRegVal();

	private:
		
		/**
		* @brief used to create a key
		* @return void
		* @throws ErrorFindingKey, ErrorOpeningKey if it doesn't find the key or open the key
		*/
		void CreateRegKey();

		/**
		* @brief used to set a key with a value
		* @return void
		* @throws ErrorFindingKey, ErrorOpeningKey if it doesn't find the key or open the key
		*/
		void setRegVal();

		HKEY m_currentUserKey = NULL;

		HKEY m_phkResult = NULL;

};

class OpeningKeyException: ExceptionClass
{
	int handleException() const override;
};

class FindingKeyException: ExceptionClass
{
	int handleException() const override;
};

class FileNotFoundException : ExceptionClass
{
	int handleException() const override;
};
