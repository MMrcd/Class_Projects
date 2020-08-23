/**************************************************************
 * File	  : PinHit.cpp
 * Project: CSCE 221 - Project 4 - Heaps
 * Author : Marcel Thio
 * Date   : 22 April 2014
 * Section: 518
 * E-mail : marcel.m.thio@tamu.edu
 *
 * PinHit, where the PinHit object is implemented
 *
 *************************************************************/
#include "PinHit.h"

PinHit::PinHit() {
	m_pin = -1;
	m_hits = 0;
}

PinHit::PinHit(int key, int value) {
	m_pin = key;
	m_hits = value;
}

void PinHit::SetKey(int pin) {
	m_pin = pin;
}

int PinHit::GetKey() const {
	return m_pin;
}

int PinHit::GetValue() const {
	return m_hits;
}

void PinHit::IncrementHits() {
	m_hits += 1;
}

int PinHit::CompareTo(const PinHit& other) const {
	if (this->m_hits == other.m_hits) {
		return 0;
	}
	else if (this->m_hits > other.m_hits) {
		return 1;
	}
	else {
		return -1;
	}
}

bool PinHit::operator==(const PinHit& other) {
	return this->m_pin == other.m_pin;
}
