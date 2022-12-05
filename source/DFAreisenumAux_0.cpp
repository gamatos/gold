#include "DFAreisenumAux_0.h"
#include <ostream>
#include <fstream>
using namespace std;

DFAreisenumAux_0::DFAreisenumAux_0(const DFAreisenumAux_0 & copy) :
	state_nr(copy.state_nr),
	s(copy.s),
	symbol_nr(copy.symbol_nr),
	cur(copy.cur),
	flags(copy.flags)
{
}

DFAreisenumAux_0::DFAreisenumAux_0(int state_nr, int symbol_nr) :
	state_nr(state_nr),
	s(state_nr*symbol_nr, 0),
	symbol_nr(symbol_nr)
{
	if (state_nr <= 1)
	{
		throw new std::runtime_error("Number of states must be greater than or equal to 1.");
	}
	flags.reserve(state_nr);
	for (int i = 1; i < state_nr; i++)
	{
		int j = symbol_nr*i - 1;
		flags.push_back(j);
		s[j] = i;
	}
}

DFA_0 DFAreisenumAux_0::getCur() const
{
	std::vector<std::vector<int>> d;
	d.reserve(state_nr);
	int bit = 1;
	for (int i = 0; i < state_nr; i++)
	{
		std::vector<int>::const_iterator b = s.begin() + symbol_nr * i;
		std::vector<int>::const_iterator e = s.begin() + symbol_nr * (i+1);
		std::vector<int> t = std::vector<int>(b, e);
		d.push_back(t);
	}
	return DFA_0(d);
}

const DFAreisenumAux_0& DFAreisenumAux_0::next()
{
	generator();
	return *this;
}

bool DFAreisenumAux_0::isLast()
{
	return islast();
}

DFAreisenumAux_0& DFAreisenumAux_0::operator=(const DFAreisenumAux_0 & rhs)
{
	state_nr = rhs.state_nr;
	s = rhs.s;
	symbol_nr = rhs.symbol_nr;
	cur = rhs.cur;
	flags = rhs.flags;

	return *this;
}

void DFAreisenumAux_0::nextflags(int i)
{
	if (i == 0)
	{
		--flags[i];
	}
	else
	{
		if (flags[i] - 1 == flags[i - 1])
		{
			flags[i] = symbol_nr * (i + 1) - 1;
			nextflags(i - 1);
		}
		else
		{
			--flags[i];
		}
	}
}

void DFAreisenumAux_0::nexticdfa()
{
	bool full = true;
	int cur_flag = flags.size() - 1;
	int cur_top = s.size() - 1;
	int cur_max = state_nr - 1;

	while(true)
	{
		for (int i = cur_top; i > flags[cur_flag]; i--)
		{
			++s[i];
			if(s[i] > cur_max)
			{			
				s[i] = 0;
			}
			else 
			{
				return;
			}
		}
		cur_top = flags[cur_flag] - 1;
		--cur_flag;
		cur_max = cur_flag + 1;		
	}
}

void DFAreisenumAux_0::generator()
{
	if (islast())
		reset();
	if (isfull())
	{
		nextflags(state_nr - 2);
		reset();
	}
	else
		nexticdfa();
}

void DFAreisenumAux_0::print()
{
	ofstream f("reisenum.txt");
	std::copy(s.begin(), s.end(), std::ostream_iterator<int>(f, " "));
	f << "\n";
	while (!islast())
	{
		generator();
		std::copy(s.begin(), s.end(), std::ostream_iterator<int>(f, " "));
		f << "\n";
		if (isfull())
		{
			f << "\n\n";
			std::copy(flags.begin(), flags.end(), std::ostream_iterator<int>(f, " "));
			f << "\n\n";
		}
	}
	f.close();
}

bool DFAreisenumAux_0::islast() const
{
	for (int i = 0; i < flags.size(); i++)
	{
		if (flags[i] != i) return false;
	}
	return isfull();
}

bool DFAreisenumAux_0::isfull() const
{
	for (int i = 0; i < flags.size() - 1; i++)
	{
		for (int j = flags[i] + 1; j != flags[i+1]; j++)
		{
			if (s[j] != i+1) return false;
		}
	}
	for (int k = flags[state_nr - 2] + 1; k <= state_nr*symbol_nr - 1; k++)
	{
		if (s[k] != state_nr - 1) return false;
	}

	return true;
}

void DFAreisenumAux_0::reset()
{
	std::fill(s.begin(), s.end(), 0);
	for (int i = 0; i < flags.size(); i++)
	{
		s[flags[i]] = i+1;
	}
}
