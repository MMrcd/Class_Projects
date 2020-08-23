/************************************************
 * File     :   Llama.h
 * Project  :   CSCE 221 Project 1, Spring 2020
 * Author   :   Marcel Thio
 * Date     :   2/12/2020
 * Section  :   518
 * Email    :   marcel.m.thio@tamu.edu
 * 
 * File to implement essentially llamastack
 *********************************************/
#pragma once
#ifndef _LLAMA_H_
#define _LLAMA_H_

/* File: Llama.h

   This file has the class declaration for the LlamaNode class
   for Project 1. See project description for details.

   You may add public and private data members to the Llama class.

   You may add public and private member functions to the Llama class.

*/


#include <stdexcept>
#include <string>
//#include <stack>
#include "LlamaNode.h"

using namespace std;


class LlamaUnderflow : public std::out_of_range {

public:

    LlamaUnderflow(const string& what) : std::out_of_range(what) { }

};


template <class T, int LN_SIZE>
class Llama {

public:

    Llama();
    Llama(const Llama<T, LN_SIZE>& other);   // copy constructor
    ~Llama();


    int size();
    void dump();
    void push(const T& data);
    T pop();


    void dup();    //  (top) A B C D -> A A B C D
    void swap();   //  (top) A B C D -> B A C D 
    void rot();    //  (top) A B C D -> C A B D
    void clear();  //  clear and reset the nodes

    T peek(int offset) const;


    // overloaded assignment operator
    //
    const Llama<T, LN_SIZE>& operator=(const Llama<T, LN_SIZE>& rhs);


    //
    // Add your public member functions & public data mebers here:
    //
    

private:


    //
    // Add your private member functions & private data mebers here:
    //
    LlamaNode<T, LN_SIZE>* current = nullptr;
    LlamaNode<T, LN_SIZE>* frontLlama = nullptr;
    LlamaNode<T, LN_SIZE>* cursor = nullptr;
    int currSpace = 0;
    int totData = 0;

};


#include "Llama.cpp"


#endif