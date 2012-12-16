// 440-mergeSort_cppw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sorter.h"

#include <stdio.h>
#include <Windows.h>


using namespace std;

// Generate a random number between 0 and 1000
int randomNumber()
{
	return (rand()%1000);
}

int _tmain(int argc, char *argv[])
{
	// Variables
    int collectionSize = 0;
    int numberOfThreads = 0;
    int lowestNumber = 0;
    bool notSorted = true;
    
    vector<int> sortedItemList;
    vector<Sorter> sorterList;


	// Get command line parameters
    if (argc != 2)
    {
    	collectionSize = atoi(argv[1]);
    	numberOfThreads = atoi(argv[2]);
    }
    else
    {
    	cout << "USAGE: arg1: collection size, arg2: number of threads\n";
		return 0;
    }

	// Create a vector with items
    vector<int> masterItemCollection(collectionSize);

    // Generate random numbers in the master item collection
    generate(masterItemCollection.begin(), masterItemCollection.end(), randomNumber);

	// Debug
	cout << "Unsorted list\n";
	
	for (auto iterator = masterItemCollection.begin(); iterator != masterItemCollection.end(); iterator++)
	{
		cout << *iterator << endl;
	}

	// Create sorter objects
	for (int iteratorIndex = 0; iteratorIndex < numberOfThreads; iteratorIndex++)
	{
		// Create new sorter
		Sorter currentSorter(&masterItemCollection, collectionSize, numberOfThreads, iteratorIndex);
		
		// Keep track of this sorter
		sorterList.push_back(currentSorter);
	}


	// Create threads
	for (auto iterator = sorterList.begin(); iterator != sorterList.end(); iterator++)
	{
		// Get a pointer to the current sorter object
		Sorter *currentSorter = &(*iterator);
		
		// Create thread
		currentSorter->startInternalThread();
	}
	
	// Wait for threads to finish
	for (auto iterator = sorterList.begin(); iterator != sorterList.end(); iterator++)
	{
		// Get a pointer to the current sorter object
		Sorter *currentSorter = &(*iterator);
			
		// Wait for thread to finish
		currentSorter->waitForInternalThreadToExit();
	}
		

    // Pointer to list to increment
    Sorter *listToIncrement = NULL;


	// Merge individual items into a giant sorted list
    while (notSorted == true)
    {
    	// Reset lowest number
    	lowestNumber = 9999;

    	// For each list
    	for (auto iterator = sorterList.begin(); iterator != sorterList.end(); iterator++)
    	{
            // Get current sorter
            Sorter *currentSorter = &(*iterator);
            
			// Is item from list a lower number than the current lowest number
    		if (currentSorter->getItem() < lowestNumber)
    		{
                // Set the new value as lowest number
    			lowestNumber = currentSorter->getItem();
                
                // Save reference to current item that we need to add number to
                listToIncrement = &(*currentSorter);
    		}
    	}
		
		// Save lowest number
		if (lowestNumber != 9999)
		{
			// Add lowest number to sorted item list
			sortedItemList.push_back(lowestNumber);
			
			// Increment list index
			listToIncrement->incrementIndex();
		}
		else
		{
			notSorted = false;
		}
    }
	
	
	// Debug
	cout << "Sorted list\n";
	
	for (auto iterator = sortedItemList.begin(); iterator != sortedItemList.end(); iterator++)
	{
		cout << *iterator << endl;
	}


	return 0;
}

