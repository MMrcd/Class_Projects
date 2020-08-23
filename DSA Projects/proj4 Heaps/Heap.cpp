/**************************************************************
 * File	  : Heap.cpp
 * Project: CSCE 221 - Project 4 - Heaps
 * Author : Marcel Thio
 * Date   : 22 April 2014
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * Heap.cpp where the majority of heap is implemented
 *
 *************************************************************/
#ifndef HEAP_CPP_
#define HEAP_CPP_
#include "Heap.h"

using namespace std;

template<class T, int m_size>
Heap<T, m_size>::Heap() {
    // initialize array
    m_array = new T[m_size];
    //cout << "Howdy2" << endl;
}

template<class T, int m_size>
Heap<T, m_size>::Heap(const Heap<T, m_size>& origHeap) {
    // initialize array
    m_array = new T[m_size];
    // copy
    for (int i = 1; i <= origHeap.endPos; i++) {
        PinHit p =  PinHit(origHeap.getValue(i).GetKey(), origHeap.getValue(i).GetValue());
        m_array[i] = p; // might need another funtion
    }
    this->type = origHeap.type;
    this->endPos = origHeap.endPos;
}

template<class T, int m_size>
bool Heap<T, m_size>::Contains(const T& needle) const {
    // go through the heap
    for (int i = 0; i < m_size; i++) {
        //if matches
        if (m_array[i] == needle) {
            return true;
        }
    }
    // if not found
    return false;
}


template<class T, int m_size>
const T* Heap<T, m_size>::Find(const T& needle) const {
    // go through the heap
    for (int i = 0; i < m_size; i++) {
        //if matches
        if (m_array[i] == needle) {
            return &m_array[i];
        }
    }
    // if not found
    return nullptr;
}

template<class T, int m_size>
T& Heap<T, m_size>::Remove() {
    if (endPos <= 0) {
        cout << "Heaps empty can't REMOVE" << endl;
    }
    T& ret = m_array[1];
    m_array[1] = m_array[endPos];
    PercolateDown(1);
    return ret;
}

template<class T, int m_size>
void Heap<T, m_size>::Insert(T& insertable) {
    const T* tPointer = Find(insertable);
    PinHit* pinPointer;
    
    // if there is said object
    if (tPointer != nullptr) {
        pinPointer = (PinHit*)&tPointer;
        pinPointer->IncrementHits();
        cout << "This ran---------------------------------------------------------------------" << endl;
    }
    else {
        // if ther is none make more room and insert and percolate up
        endPos++;
        m_array[endPos] = insertable;
        //cout<< "_____________________START__________________\n"<< m_array[endPos].GetKey() << endl;
        PercolateUp(endPos);
    }
    pinPointer = nullptr;
    tPointer = nullptr;
}

template<class T, int m_size>
void Heap<T, m_size>::PercolateUp(int index) {
    T ret = m_array[index];
    int hole = endPos;
    
    
    
    // find out if min or max
    if (type == -1) {
        // min
        for (; hole >= 1 && (ret.CompareTo(m_array[hole / 2]) < 0 && hole / 2 != 0); hole /= 2) {
            //cout << m_array[hole].GetValue() << "|"<< m_array[hole/2].GetValue() <<endl;
            m_array[hole] = m_array[hole / 2]; // swap, from child to parent
            // print
            //cout << "swap\n hole/2|hole :" << hole / 2 << " | " << hole << endl;
            //cout << m_array[index].CompareTo(m_array[(hole / 2)/2]) << endl;
            //cout << m_array[index].GetKey() <<" "<< m_array[index].GetValue() << "|" << (hole / 2) / 2 << " : " << m_array[(hole / 2) / 2].GetValue() << endl;
        }
        m_array[hole] = ret;
    }
    else if (type == 1) {
        // max
        for (; hole >= 1 && (ret.CompareTo(m_array[hole / 2]) >= 0 && hole / 2 != 0); hole /= 2) {
            //cout << m_array[hole].GetValue() << "|"<< m_array[hole/2].GetValue() <<endl;
            m_array[hole] = m_array[hole / 2]; // swap, from child to parent
            // print
            //cout << "swap\n hole/2|hole :" << hole / 2 << " | " << hole << endl;
            //cout << m_array[index].CompareTo(m_array[(hole / 2)/2]) << endl;
            //cout << m_array[index].GetKey() <<" "<< m_array[index].GetValue() << "|" << (hole / 2) / 2 << " : " << m_array[(hole / 2) / 2].GetValue() << endl;
        }
        m_array[hole] = ret;
    }
    else {
        cout << "error heap type not picked";
    }
}

template<class T, int m_size>
void Heap<T, m_size>::PercolateDown(int index) {
    int childIndex;
    T actVal = m_array[index];
    
    // find out if min or max
    if (type == -1) {
        // min
        for (; index * 2 <= endPos; index = childIndex) {
            childIndex = index * 2;

            if (childIndex != endPos && m_array[childIndex+1].CompareTo(m_array[childIndex]) < 0) {
                childIndex++;
            }
            if (m_array[childIndex].CompareTo(actVal) < 0 && m_array[childIndex].GetKey() != -1) {
                m_array[index] = m_array[childIndex];
            }
            else {
                break;
            }
        }
        m_array[index] = actVal;
    }
    else if (type == 1) {
        //max
        for (; index * 2 <= endPos; index = childIndex) {
            childIndex = index * 2;

            if (childIndex != endPos && m_array[childIndex + 1].CompareTo(m_array[childIndex]) >= 0) {
                childIndex++;
            }
            if (m_array[childIndex].CompareTo(actVal) >= 0 && m_array[childIndex].GetKey() != -1) {
                m_array[index] = m_array[childIndex];
            }
            else {
                break;
            }
        }
        m_array[index] = actVal;
    }
    else {
        cout << "error heap type not picked";
    }
    endPos--;
    
}

template<class T, int m_size>
void Heap<T, m_size>::setType(int i)
{
    type = i;
}

template<class T, int m_size>
Heap<T, m_size>::~Heap() {
    delete[]m_array;
}

template<class T, int m_size>
void Heap<T, m_size>::printArray()
{
    cout << "--------------------------------------------------------\n";
    for (int i = 0; i <= endPos; i++) {
        cout << m_array[i].GetKey() << " | " << m_array[i].GetValue() << " | " << i << endl;
    }
}

template<class T, int m_size>
T& Heap<T, m_size>::getValue(int i) const{
    return m_array[i];
}

#endif /* HEAP_CPP_ */