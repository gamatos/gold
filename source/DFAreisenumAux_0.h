#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include "DFA_0.h"
#include "DFAenumerator.h"
#include <boost/dynamic_bitset.hpp>


class DFAreisenumAux_0
{
public:
	DFAreisenumAux_0(const DFAreisenumAux_0 &copy);
	DFAreisenumAux_0(int state_nr, int symbol_nr);

	void print();

	DFA_0 getCur() const;
	const DFAreisenumAux_0& next();

	bool isLast();

	DFAreisenumAux_0 & operator=(const DFAreisenumAux_0 &rhs);
	std::string name() { return "reisaux"; };



private:
	int state_nr;
	int symbol_nr;
	std::vector<std::vector<int>> cur;

	std::vector<int> flags;

	std::vector<int> s;

	void nextflags(int i);
	void nexticdfa();
	void generator();

	bool islast() const;
	bool isfull() const;

	void reset();

	int base() const {
		return state_nr - 1;
	}
};