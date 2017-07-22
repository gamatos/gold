#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include "DFA_0.h"
#include "DFAreisenumAux_0.h"
#include "DFAenumerator_0.h"


class DFAreisenum_0 : public DFAenumerator_0
{
public:
	DFAreisenum_0(int max_state_nr, int symbol_nr);

	DFA_0 getCur() const;
	const DFAreisenum_0& next();

	bool isLast();

	void DFAreisenum_0::reset();
	std::string name() { return "reis"; };
	void setMaxStates(int m);
private:
	int max_state_nr;
	int cur_state_nr = 1;
	bool one_state_final = 0;
	int symbol_nr;
	DFAreisenumAux_0 cur_enum;

};