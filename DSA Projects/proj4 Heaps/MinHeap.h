/**************************************************************
 * File	  : MinHeap.H
 * Project: CSCE 221 - Project 4 - Heaps
 * Author : Marcel Thio
 * Date   : 22 April 2014
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * MinHeap, where object MinHeap was defined
 *
 *************************************************************/
#ifndef MINHEAP_H_
#define MINHEAP_H_

#include "Heap.h"
template<class T, int m_size> 
class MinHeap : public Heap<T, m_size>
{
public:
	MinHeap()
	: Heap<T, m_size>() {
		Heap<T, m_size>::setType(-1);
	}
	
	MinHeap(const Heap<T, m_size>& origHeap)
		: Heap<T, m_size>(origHeap) {
		Heap<T, m_size>::setType(-1);
	}
};
#endif // !MINHEAP_H