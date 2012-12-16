// 440-mergeSort_cppw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

using namespace std;

DWORD Sum; // shared data by the threads

// The thread runs in a separate function
DWORD WINAPI Summation(PVOID Param)
{
	DWORD Upper = *(DWORD *)Param;

	for (DWORD i = 0; i <= Upper; i++)
	{
		Sum += i;
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD threadId;
	HANDLE threadHandle;
	int param;

	param = 10;

	// create thread
	threadHandle = CreateThread(NULL, 0, Summation, &param, 0, &threadId);

	if (threadHandle != NULL)
	{
		WaitForSingleObject(threadHandle, INFINITE); // join threads
		CloseHandle(threadHandle);
		printf("sum = %d\n", Sum);
	}

	return 0;
}

