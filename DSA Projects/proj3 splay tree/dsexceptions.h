/*****************************************
** File:    dsexceptions.h
** Project: CSCE 221 Project 3
** Author:  Marcel Thio
** Date:    March 31, 2020
** Section: 518
** E-mail:  marcel.m.thio@tamu.edu
**
**  Exceptions to be thrown
**
*******************************************/

#ifndef DSEXCEPTIONS_H
#define DSEXCEPTIONS_H

#include <iostream>
#include <exception>
using namespace std;

class UnderflowException : public exception {
	virtual const char* what() const throw() {
		return "UNDERFLOW EXCEPTUION EXCEPTION:";
	}
};

class IllegalArgumentException : public exception {
	virtual const char* what() const throw() {
		return "ILLEGAL ARGUMENT EXCEPTION:";
	}
};

class ArrayindexOutOfBoundsException: public exception {
	virtual const char* what() const throw() {
		return "ARRAY INDEX OUT OF BOUNDS EXCEPTION:";
	}
};

class IteratorOutOfBoundsException : public exception {
	virtual const char* what() const throw() {
		return "ITERATOR OUT OF BOUNDS EXCEPTION:";
	}
};

class IteratorMismatchException : public exception {
	virtual const char* what() const throw() {
		return "ITERATOR MISMATCH EXCEPTION:";
	}
};
class IteratorUninitializedException : public exception {
	virtual const char* what() const throw() {
		return "ITERATOR UNINITIALIZED EXCEPTION:";
	}
};
#endif