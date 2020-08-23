/**************************************************************
 * File	  : Driver.cpp
 * Project: CSCE 221 - Project 4 - Heaps
 * Author : Marcel Thio
 * Date   : 22 April 2014
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * Driver, where hack and builing of heaps is ran and implemented
 *
 *************************************************************/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "PinHit.h"
#include "Heap.h"
#include "MinHeap.h"
#include "MaxHeap.h"

using namespace std;

// global variable for type of heap
std::string heapType = "--max";

//forward declare so I can define it below main
void printGreeting();
void vectorChecker(vector<PinHit> ret);

std::vector<PinHit> ReadPins(char* fileName, int* totalHits);

template<class T, int m_size>
Heap<T, m_size>* BuildHeap(std::vector<T> PinHits, int slots);

// provided
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, std::vector<T> PinHits, int totalHits);

int main(int argc, char* argv[]) {
	int* tHits = new int(0);
	printGreeting();
	vector<PinHit> vPhit(ReadPins(argv[1], tHits));
	//cout << "reddit" << endl;
	//vectorChecker(vPhit); // just to check the vector is correct
	heapType = argv[2];

	Heap<PinHit, 10001>* heap = BuildHeap<PinHit, 10001>(vPhit, *tHits);
	//heap->printArray();
	//heap->Remove();
	//heap->printArray();
	//cout << *tHits;
	cout << Hack(heap, vPhit, *tHits);

	delete heap;
	heap = nullptr;
	// delete pointers
	delete tHits;
	tHits = nullptr;

	return EXIT_SUCCESS;
}

// prints your name and section
void printGreeting() {
	std::cout << "Marcel Thio, Section 518" << std::endl;
}

void vectorChecker(vector<PinHit> ret) {
	for (unsigned int i = 0; i < ret.size(); i++) {
		cout << ret.at(i).GetKey() << " has " << ret.at(i).GetValue() << " hits" << endl;
	}
}

// implement these two functions
std::vector<PinHit> ReadPins(char* fileName, int* totalHits) {
	ifstream in(fileName);
	vector<PinHit> ret;
	if (in.is_open()) {
		int num;
		bool sameNum = false;
		// read through the file
		while (in >> num) {
			// check if the number is in vector
			//cout << num << endl;
			*totalHits += 1;
			for (unsigned int i = 0; i < ret.size(); i++) {
				// if it matches increment
				if (num == ret.at(i).GetKey()) {
					sameNum = true;
					ret.at(i).IncrementHits();
					
					//cout << "HIT" << endl;
				}
			}
			// if there are no matches add to vector
			if (!sameNum) {
				PinHit newPin(num, 1);
				ret.push_back(newPin);
			}
			else {
				sameNum = false;
			}
		}
		in.close();
	}
	else {
		cerr << "No file found\n";
	}
	return ret;
}

template<class T, int m_size>
Heap<T, m_size>* BuildHeap(std::vector<T> PinHits, int slots) {
	Heap <T, m_size>* ret = nullptr;
	if (heapType == "--min") {
		ret = new MinHeap<T, m_size>();
	}
	else if (heapType == "--max") {
		ret = new MaxHeap<T, m_size>();
	}
	else {
		ret = new Heap<T, m_size>();
	}
	for (unsigned int i = 0; i < PinHits.size(); i++) {
		ret->Insert(PinHits.at(i));
		//cout << "This yupyup" << endl;
	}
	return ret;
	//cout << "This yupyup" << endl;
}

// provided
template<class T, int m_size>
int Hack(Heap<T, m_size>* heap, std::vector<T> PinHits, int totalHits) {

	int UPPER_BOUND = totalHits; // used for failsafes

	/*
	* His fictional bank with fictional cards and
	* "normal pins" will allow you to incorrectly attempt
	* to access his card 3 times per hour. You have from
	* the start of the assignment to the end to hack as
	* many accounts as possible (14 days * 24 hr/day * 3
	* attempts/hr = 1008 attempts per card)
	*/
	int MAX_ATTEMPTS = 1008;

	int hackAttemptsLeft = MAX_ATTEMPTS;
	int successfulHacks = 0;

	srand(time(NULL)); // seeds our random generator with the current time  	
	int randomNumHits = rand() % totalHits; // generates a random hit between 0 and total hits	
	//randomNumHits = 0; // change this if you want to hardcode in your hits for a specific pin
	int curHits = 0; // our variable for crawling
	int randomIndex = -1; // the index where our new random pinhit lives
	int newHits = 0; // number of hits in new "random" pin
	int failSafe = 0; // always good to have one of these in what could be an infinite loop

	/*
	* Linearly searches through PinHits until
	* we've accrued enough hits to reach our random hits
	* which will then determine the next pin to try to hack.
	* We use newHits to make sure we don't pick a random pin
	* that's not in our heap.
	*/
	PinHit curPinHit;
	while (newHits == 0 && failSafe < UPPER_BOUND) {

		for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
			curHits += PinHits[i].GetValue();
			randomIndex = i;
		}
		// should have found the random pin by now
		curPinHit = PinHits[randomIndex];
		newHits = curPinHit.GetValue(); // make sure it's actually in our heap
		std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
		failSafe++;
	}

	// let's make a copy of the heap so we don't modify the original.
	Heap<T, m_size>* heapCopy;

	if (heapType == "--min") {
		heapCopy = new MinHeap<T, m_size>(*heap);
	}
	else if (heapType == "--max") {
		heapCopy = new MaxHeap<T, m_size>(*heap);
	}
	else {
		heapCopy = new Heap<T, m_size>(*heap);
	}

	failSafe = 0;

	PinHit defaultPin;

	// exit once hacking 10000 accounts, either a hacking prodigy or something is wrong
	int MAX_NUM_HACKS = 10000;

	while (0 < hackAttemptsLeft && successfulHacks < MAX_NUM_HACKS) {

		// grabs our root
		PinHit topOfHeap = heapCopy->Remove();
		if (topOfHeap == defaultPin)
			break;

		std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() << " our last attempt" << std::endl;

		if (hackAttemptsLeft == 1)
			std::cout << topOfHeap.GetKey() << ", " << topOfHeap.GetValue() << " our last attempt" << std::endl;

		hackAttemptsLeft--;

		// account was hacked!
		if (topOfHeap == curPinHit) {
			delete heapCopy;
			std::cout << "We got them!" << std::endl;
			successfulHacks++;

			// reset our heap
			if (heapType == "--min") {
				heapCopy = new MinHeap<T, m_size>(*heap);
			}
			else if (heapType == "--max") {
				heapCopy = new MaxHeap<T, m_size>(*heap);
			}
			else {
				heapCopy = new Heap<T, m_size>(*heap);
			}

			// reset
			hackAttemptsLeft = MAX_ATTEMPTS;
			randomNumHits = rand() % totalHits;
			curHits = 0;
			randomIndex = -1;
			newHits = 0;
			failSafe = 0;
			while (newHits == 0 && failSafe < UPPER_BOUND) {

				for (unsigned int i = 0; i < PinHits.size() && curHits <= randomNumHits; i++) {
					curHits += PinHits[i].GetValue();
					randomIndex = i;
				}
				// should have found the random pin by now
				curPinHit = PinHits[randomIndex];
				newHits = curPinHit.GetValue(); // make sure it's actually in our heap
				std::cout << "Random Pin: [" << curPinHit.GetKey() << ", " << curPinHit.GetValue() << "] found!" << std::endl;
				failSafe++;
			}

			std::cout << "Valid Random Pin: " << curPinHit.GetKey() << " found!" << std::endl;
		}
	}
	delete heapCopy;
	heapCopy = nullptr;
	return successfulHacks;

}