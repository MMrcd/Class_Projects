/************************************************
 * File     :   Llama.cpp
 * Project  :   CSCE 221 Project 1, Spring 2020
 * Author   :   Marcel Thio
 * Date     :   2/12/2020
 * Section  :   518
 * Email    :   marcel.m.thio@tamu.edu
 * 
 * File to implement essentially llamastack
 *********************************************/
#ifndef _LLAMA_CPP_
#define _LLAMA_CPP_

#include "Llama.h"
//#include <stack>


// constructor
template<class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama()
{	
	// create a new LlamaNode and set current and next Llama pinter
	frontLlama = new LlamaNode<T, LN_SIZE>;
	current = frontLlama;
	//frontLlama->arr = new T[LN_SIZE];
}

// copy constructor
template<class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama(const Llama<T, LN_SIZE>& other)
{
	// create a new LlamaNode and set current and next Llama pointer
	this->frontLlama = new LlamaNode<T, LN_SIZE>;
	this->current = this->frontLlama;
	
	// copy first node find how many node to traverse trough
	int llamas = 0;
	int max = LN_SIZE-1;
	LlamaNode<T, LN_SIZE>* cursor1;
	//cout<<" index of: " << 1 << " | " << other.current << endl;
	//cout << "RUNS HERE ----------1\n";
	for (cursor1 = other.frontLlama; cursor1 != NULL; cursor1 = cursor1->m_next) {
		llamas++;
		if (cursor1->m_next == NULL) {
			// for loop to iterate through the first llama in the order to get data in
			if (cursor1 == other.current) {
				max = other.currSpace-1;
			}
			for (int i = 0; i <= max; ++i) {
				this->push(cursor1->arr[i]);
			}
		}
	}
	//cout << "RUNS HERE ----------2\n";
	// if theres more than 1 llama using llamas varible iterate
	while (llamas > 1) {
		llamas--;
		max = LN_SIZE - 1;
		cursor1 = other.frontLlama;
		//cout << "RUNS HERE ----------3\n";
		// iterate to next llama after the first llama
		for (int i = 1; i < llamas; ++i) {
			cursor1 = cursor1->m_next;
		}
		if (cursor1 == other.current) {
			max = other.currSpace - 1;
		}
		//cout << "RUNS HERE ----------4\n";
		if (cursor1 != other.current && cursor1 == other.frontLlama) {
			max = -1;
			LlamaNode<T, LN_SIZE>* throwaway = new LlamaNode<T, LN_SIZE>;
			// set pointer for this one
			throwaway->m_next = this->frontLlama;
			this->frontLlama = throwaway;
			throwaway = NULL;
		}
		//cout << "RUNS HERE ----------5\n";
		for (int i = 0; i <= max; ++i) {
			
			//cout << " index of: "<< i<<" | "<< cursor1 << endl;
			this->push(cursor1->arr[i]);	
		}
		//cout << "RUNS HERE ----------6\n";
	}
	cursor1 = NULL;
}

// destructor
template<class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama()
{
	clear();
	frontLlama = nullptr;
	current = nullptr;
	cursor = nullptr;
}

// returns the amount of data has been stored
template<class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size()
{
	return totData;
}

// print out all the data based on the llamas in order
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dump()
{
	int index = currSpace -1;
	cerr << "***** Llama Stack Dump*****" << endl;
	cerr<<"LN_SIZE = "<<LN_SIZE<<endl;
	cerr << "# of items in the stack = " << totData << endl;
	// show conunt of use in constuctors and destructors
	frontLlama->report();
	// checks if firstLlama is the same as the current llama we are filling
	if (current != frontLlama) {
		cerr << "This stack has an extra node at "<< frontLlama << endl;
	}
	else{
		cerr << "This stack does not have an extra node." << endl;
	}
	// goes through the llama node and print their location
	for (cursor = current; cursor != NULL; cursor = cursor->m_next) {
		cerr << "----- "<<cursor<<" -----"<<endl;
		// goes thorugh the filled arrays and print their values
		for (int i = index; i >= 0 ; --i){
			//cout << "index is " << i<<endl;
			cerr << cursor->arr[i] << endl;
			//cout << "loop check 1.1" << endl;
		}
		index = LN_SIZE - 1;
		cerr << endl;
		//cout << "loop check 1.2" << endl;
	}
	cerr << "----- " << "bottom of stack" << " -----" << endl;
	cerr << "**************************" << endl;
}
// push in the data to llama and add new nodes when necessary
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data)
{
	// check if current llama is full and move current to new front llama if no llama in front
	if (currSpace == LN_SIZE &&  current == frontLlama) {
		cursor = new LlamaNode<T, LN_SIZE>();
		// reassign front llama
		cursor->m_next = frontLlama;
		frontLlama = cursor;
		currSpace = 0;
		current = frontLlama;
	}
	// if current llama is behind a llama and is full already change pointer
	if (currSpace == LN_SIZE && current != frontLlama) {
		current = frontLlama;
		currSpace = 0;
	}
	// does the actual adding of datas
	current->arr[currSpace] = data;
	currSpace++;
	totData++;
}

template<class T, int LN_SIZE>
T Llama<T, LN_SIZE>::pop()
{
	// if totData is zero and pop is called throw LlamaUnderFlow
	if (totData == 0) {
		throw LlamaUnderflow("poping empty stack");
	}
	totData--;
	T ret = current->arr[currSpace-1];
	// if current space taken is less than or equal to than half of the LN_SIZE delete front llama
	if (( LN_SIZE == 1||(((currSpace-1) / 1.0) <= (LN_SIZE / 2.0))) && current != frontLlama) {
		frontLlama->m_next = nullptr;
		delete frontLlama;
		frontLlama = current;
	}
	// if current has nos space then change current position
	if (currSpace == 1 && current == frontLlama) {
		currSpace = LN_SIZE;
		current = current->m_next;
	}
	// just change the current space
	else{
		currSpace--;
	}
	return ret;
}
//  (top) A B C D -> A A B C D
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup()
{	
	// make sure that theres enough items to duplicate
	if (totData == 0) {
		throw LlamaUnderflow("duplicating empty stack");
	}
	// make a new variable equal to current top element and push it in
	T n = current->arr[currSpace - 1];
	this->push(n);
}
//  (top) A B C D -> B A C D 
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::swap()
{
	// if there are no item to swap around throw exception
	if (totData < 2) {
		throw LlamaUnderflow("not enough items to swap");
	}
	// pop the last two, saving two variables in the process and pushing it in a swaped order
	T a = this->pop();
	T b = this->pop();
	this->push(a);
	this->push(b);
}
//  (top) A B C D -> C A B D
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::rot()
{
	// if there are not enough items to rotate around throw exception
	if (totData < 3) {
		throw LlamaUnderflow("not enough items to rotate");
	}
	//pop the three items, then switch the around the values using push
	T a = this->pop();
	T b = this->pop();
	T c = this->pop();

	this->push(b);
	this->push(a);
	this->push(c);
}
// just clear and set null all variables
template<class T, int LN_SIZE>
void Llama<T, LN_SIZE>::clear()
{
	cursor = frontLlama;
	// deep clense of nodes
	while (cursor != NULL) {
		frontLlama = cursor;
		cursor = cursor->m_next;
		delete frontLlama;
	}
	// set everyting to original values or null
	cursor = NULL;
	frontLlama = NULL;
	current = NULL;
	currSpace = 0;
	totData = 0;
}

template<class T, int LN_SIZE>
T Llama<T, LN_SIZE>::peek(int offset) const
{
	// if offset is too big throw llama underflow
	if (totData <offset) {
		throw LlamaUnderflow("offset more like oofset, offset is larger than total amount of data contained in the stack");
	}
	int index = currSpace-1;
	// use for loop to iterate through llamas
	for (LlamaNode<T,LN_SIZE> *cursor1 = current; cursor1 != NULL && offset>=0; cursor1 = cursor1->m_next) {
		// for loop to iterate through the loop
		for (int i = index; i >= 0 && offset >= 0; --i) {
			if (offset == 0) {
				T data = cursor1->arr[i];
				cursor1 = NULL;
				return data;
			}
			offset--;
		}
		index = LN_SIZE - 1;
	}
}

template<class T, int LN_SIZE>
const Llama<T, LN_SIZE>& Llama<T, LN_SIZE>::operator=(const Llama<T, LN_SIZE>& rhs)
{
	// TODO: insert return statement here
	this->clear();

	// create a new LlamaNode and set current and next Llama pointer
	this->frontLlama = new LlamaNode<T, LN_SIZE>;
	this->current = this->frontLlama;

	// copy first node find how many node to traverse trough
	int llamas = 0;
	int max = LN_SIZE - 1;
	LlamaNode<T, LN_SIZE>* cursor1;
	//cout << " index of: " << 1 << " | " << rhs.current << endl;
	//cout << "RUNS HERE ----------1\n";
	for (cursor1 = rhs.frontLlama; cursor1 != NULL; cursor1 = cursor1->m_next) {
		llamas++;
		if (cursor1->m_next == NULL) {
			// for loop to iterate through the first llama in the order to get data in
			if (cursor1 == rhs.current) {
				max = rhs.currSpace - 1;
			}
			for (int i = 0; i <= max; ++i) {
				this->push(cursor1->arr[i]);
			}
		}
	}
	//cout << "RUNS HERE ----------2\n";
	// if theres more than 1 llama using llamas varible iterate
	while (llamas > 1) {
		llamas--;
		max = LN_SIZE - 1;
		cursor1 = rhs.frontLlama;
		//cout << "RUNS HERE ----------3\n";
		// iterate to next llama after the first llama
		for (int i = 1; i < llamas; ++i) {
			cursor1 = cursor1->m_next;
		}
		if (cursor1 == rhs.current) {
			max = rhs.currSpace - 1;
		}
		//cout << "RUNS HERE ----------4\n";
		if (cursor1 != rhs.current && cursor1 == rhs.frontLlama) {
			max = -1;
			LlamaNode<T, LN_SIZE>* throwaway = new LlamaNode<T, LN_SIZE>;
			// set pointer for this one
			throwaway->m_next = this->frontLlama;
			this->frontLlama = throwaway;
			throwaway = NULL;
		}
		//cout << "RUNS HERE ----------5\n";
		for (int i = 0; i <= max; ++i) {

			//cout << " index of: " << i << " | " << cursor1 << endl;
			this->push(cursor1->arr[i]);
		}
		//cout << "RUNS HERE ----------6\n";
	}
	cursor1 = NULL;

	return *this;
}

#endif