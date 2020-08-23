/**************************************************************
 * File	  : PinHit.H
 * Project: CSCE 221 - Project 4 - Heaps
 * Author : Marcel Thio
 * Date   : 22 April 2014
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * PinHit, where object pinhit was defined
 *
 *************************************************************/
#ifndef PINHIT_H_
#define PINHIT_H_

class PinHit {

public:
	PinHit();
	PinHit(int key, int value);
	void SetKey(int pin);
	int GetKey() const;
	int GetValue() const;
	void IncrementHits();
	int CompareTo(const PinHit& other) const;
	bool operator==(const PinHit& other);

private:

	int m_pin, m_hits;
};
//#include "PinHit.cpp"
#endif /* PinHit_H_ */