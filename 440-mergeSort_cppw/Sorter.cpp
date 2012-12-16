//
//  Sorter.cpp
//  mergeSort_cpp
//
//  Created by Andrew Breja on 06/12/2012.
//  Copyright (c) 2012 Andrew Breja. All rights reserved.
//


#include "stdafx.h"
#include "Sorter.h"

using namespace std;


// Constructor
Sorter::Sorter(vector<int> *givenMasterItemCollection, int givenNumberOfItems, int givenNumberOfThreads, int givenThreadId)
{
    // Set given variables
    this->masterItemCollection = givenMasterItemCollection;
    this->numberOfItems = givenNumberOfItems;
    this->numberOfThreads = givenNumberOfThreads;
    this->threadId = givenThreadId;
    
    // Initialize variables
    this->indexLocation = 0;
}


// Calculate positions
void Sorter::calculatePositions()
{
    // Beginning position
    this->beginningPosition = (this->numberOfItems / this->numberOfThreads) * this->threadId;
    
    // Ending position
    this->endingPosition = this->beginningPosition + (this->numberOfItems / this->numberOfThreads) - 1;
    
    // The last thread gets the slack
    if ((this->threadId == this->numberOfThreads - 1) && (this->endingPosition < this->numberOfItems - 1))
    {
        this->endingPosition = this->numberOfItems - 1;
    }
}


int Sorter::getId()
{
	return this->threadId;
}

// Get sorted items
int Sorter::getItem()
{
    // Get an item at the given index location
    try
    {
        return this->workingItemCollection.at(this->indexLocation);
    }
    catch (out_of_range& oor)
    {
        return 9999;
    }
    
}


// Set index location
void Sorter::incrementIndex()
{
    this->indexLocation++;
}


// Start the thread
void Sorter::startInternalThread()
{
	//return (pthread_create(&_theThread, NULL, internalThreadFunction, this) == 0);
	//LPDWORD thisThreadId = LPDWORD(this->threadId);

	//	int *functionPointer = this->run;

	//int (*runPointer)() = this->run;
	//(LPTHREAD_START_ROUTINE)

	_theThread = CreateThread(NULL, 0, internalThreadFunction, this, 0, NULL); 
}


// Wait for thread to finish
void Sorter::waitForInternalThreadToExit()
{
	//(void) pthread_join(_theThread, NULL);
	if (_theThread != NULL)
	{
		WaitForSingleObject(_theThread, INFINITE);
		CloseHandle(_theThread);
	}
}


// Calls the internal thread function
DWORD WINAPI Sorter::internalThreadFunction(void *givenSorterPointer)
{
	//Sorter *sorterPointer = static_cast<Sorter*>(givenSorterPointer);
	
	Sorter *sorterPointer = (Sorter*) givenSorterPointer;

	sorterPointer->run();

	return 0;
}


// This is the bread and butter of the whole operation
void Sorter::run()
{
	// Calculate beginning and ending positions
    this->calculatePositions();
    
    // For each - using beginning and ending positions
    for (int iteratorIndex = this->beginningPosition; iteratorIndex <= this->endingPosition; iteratorIndex++)
    {
        // Copy to temporary local array
        this->workingItemCollection.push_back(this->masterItemCollection->at(iteratorIndex));
    }
    
    // Sort working item collection
    sort(this->workingItemCollection.begin(), this->workingItemCollection.end());

}

