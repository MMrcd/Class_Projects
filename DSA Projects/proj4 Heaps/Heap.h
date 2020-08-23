/**************************************************************
 * File	  : Heap.H
 * Project: CSCE 221 - Project 4 - Heaps
 * Author : Marcel Thio
 * Date   : 22 April 2014
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * Heap, where object Heap was defined
 *
 *************************************************************/
#ifndef HEAP_H_
#define HEAP_H_

#include "PinHit.h"
#include <iostream>

template<class T, int m_size> class Heap {
protected:
	int type = 0; // -1 is min and 1 is max heap
	int endPos = 0; // is the index of the last position 
public:

	// required functions by UML
	Heap();
	Heap(const Heap<T, m_size>& origHeap);
	bool Contains(const T& needle) const;
	const T* Find(const T& needle) const;
	T& Remove();
	void Insert(T& insertable);
	void PercolateUp(int index);
	void PercolateDown(int index);

	// student-made functions below
	void setType(int i);
	~Heap();
	void printArray();

	T& getValue(int i) const;
private:

	// UML-required member variables
	T* m_array;

	// student-made member variables

};

#include "Heap.cpp"
#endif /* HEAP_H_ */