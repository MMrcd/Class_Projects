/**************************************************************
 * File	  : MaxHeap.H
 * Project: CSCE 221 - Project 4 - Heaps
 * Author : Marcel Thio
 * Date   : 22 April 2014
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * MaxHeap, where object MaxHeap was defined
 *
 *************************************************************/
#ifndef MAXHEAP_H_
#define MAXHEAP_H_



#include "Heap.h"
template<class T, int m_size> 
class MaxHeap : public Heap<T, m_size>
{
public:
	MaxHeap()
		: Heap<T, m_size>() {
		Heap<T, m_size>::setType(1);
		//cout << "Howdy" << endl;
	}

	MaxHeap(const Heap<T, m_size>& origHeap)
		: Heap<T, m_size>(origHeap) {
		Heap<T, m_size>::setType(1);
	}
};

#endif // !MAXHEAP_H