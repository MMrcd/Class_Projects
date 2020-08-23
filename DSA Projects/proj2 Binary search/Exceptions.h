/*****************************************
** File:    Exceptions.h
** Project: CSCE 221 Project 2
** Author:  Marcel Thio
** Date:    March 5, 2020
** Section: 518
** E-mail:  marcel.m.thio@tamu.edu
**
**  Exceptions to be thrown
**
*******************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>
using namespace std;

class ItemNotFound : public exception {
	virtual const char* what() const throw() {
		return "ITEM NOT FOUND EXCEPTION:";
	}
};

class CommandNotFound : public exception {
	virtual const char* what() const throw() {
		return "INVALID COMMAND EXCEPTION:";
	}
};

class ArgumentNotFound : public exception {
	virtual const char* what() const throw() {
		return "NULL ARGUMENT EXCEPTION:";
	}
};

class NodeNotFound : public exception {
	virtual const char* what() const throw() {
		return "NODE NOT FOUND EXCEPTION:";
	}
};
#endif