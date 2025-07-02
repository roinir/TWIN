#pragma once
#include <windows.h>
#include <iostream>


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
		void m_CreateRegKey();

		/**
		* @brief used to set a key with a value
		* @return void
		* @throws ErrorFindingKey, ErrorOpeningKey if it doesn't find the key or open the key
		*/
		void m_setRegVal();

		HKEY m_currentUserKey = NULL;

		HKEY m_phkResult = NULL;

};

class ErrorOpeningKey
{
	// left blank intentionally
};

class ErrorFindingKey
{
	// left blank intentionally
};
