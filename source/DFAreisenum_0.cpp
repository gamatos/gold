#include "DFAreisenum_0.h"
#include <ostream>
#include <fstream>
using namespace std;

DFAreisenum_0::DFAreisenum_0(int max_state_nr, int symbol_nr) :
	max_state_nr(max_state_nr),
	symbol_nr(symbol_nr),
	cur_enum(2, symbol_nr),
	cur_state_nr(1)
{

}

DFA_0 DFAreisenum_0::getCur() const
{
	if (cur_state_nr == 1)
	{
		std::vector<std::vector<int>> transitions = { {0,0} };
		return DFA_0(transitions);
	}
	return cur_enum.getCur();
}

const DFAreisenum_0& DFAreisenum_0::next()
{
	if (cur_state_nr == 1)
	{
		cur_state_nr += one_state_final;
		one_state_final = !one_state_final;
	}
	else if (cur_enum.isLast())
	{
		if (cur_state_nr == max_state_nr)
			reset();
		else
		{
			++cur_state_nr;
			cur_enum = DFAreisenumAux_0(cur_state_nr, symbol_nr);
		}
	}
	else
	{
		cur_enum.next();
	}

	return *this;
}


bool DFAreisenum_0::isLast()
{
	if (cur_enum.isLast())
	{
		if (cur_state_nr == max_state_nr)
		{
			return true;
		}
	}
	return false;
}

void DFAreisenum_0::reset()
{
	cur_enum = DFAreisenumAux_0(2, symbol_nr);
	cur_state_nr = 1;
	one_state_final = false;
}

void DFAreisenum_0::setMaxStates(int m)
{
	if (m < cur_state_nr)
	{
		reset();
	}
	max_state_nr = m;
}
