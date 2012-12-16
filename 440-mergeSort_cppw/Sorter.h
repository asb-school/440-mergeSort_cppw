//
//  Sorter.h
//  mergeSort_cpp
//
//  Created by Andrew Breja on 15/12/2012.
//  Copyright (c) 2012 Andrew Breja. All rights reserved.
//

#include "stdafx.h"

using namespace std;


class Sorter
{
public:
	
	// Constructor
	Sorter(vector<int> *givenMasterItemCollection, int givenNumberOfItems, int givenNumberOfThreads, int givenThreadId);
	
	// Functions
	int getItem();
	int getId();
	void incrementIndex();
	bool startInternalThread();
	void waitForInternalThreadToExit();
	
private:
	
	// Variables
	vector<int> workingItemCollection;
	vector<int> *masterItemCollection;
	
	int numberOfItems;
	int numberOfThreads;
	LPDWORD threadId;
	
	int beginningPosition;
	int endingPosition;
	
	int indexLocation;
	HANDLE _theThread;
	
	// Functions
	void calculatePositions();
	static void *internalThreadFunction(void *givenSorterPointer);
	DWORD WINAPI run();
};
