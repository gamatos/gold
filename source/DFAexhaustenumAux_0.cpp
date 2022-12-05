#include "DFAexhaustenumAux_0.h"
#include <stdlib.h>
#include <stdexcept>
#include <cmath>

DFAexhaustenumAux_0::DFAexhaustenumAux_0(int state_nr) :
	state_nr(state_nr),
	max_edge_states(pow(state_nr, (state_nr * 2)))
{
	cur = std::vector<std::vector<int>>(state_nr, std::vector<int>(2, 0));
}

DFAexhaustenumAux_0::DFAexhaustenumAux_0(const DFAexhaustenumAux_0 & copy) :
	state_nr(copy.state_nr),
	max_edge_states(copy.max_edge_states),
	cur(copy.cur),
	cur_nr(copy.cur_nr)
{
}

DFAexhaustenumAux_0 DFAexhaustenumAux_0::operator=(const DFAexhaustenumAux_0 & rhs)
{
	return DFAexhaustenumAux_0(rhs);
}


DFAexhaustenumAux_0 DFAexhaustenumAux_0::get(const int statenr)
{
	return DFAexhaustenumAux_0(statenr);
}


DFA_0 DFAexhaustenumAux_0::getCur() const
{
	return DFA_0(cur);
}

const DFAexhaustenumAux_0 & DFAexhaustenumAux_0::next()
{
	++cur_nr;
	int i = 0;
	int k = 0;
	int incr = 1;
	while (cur[i][k] == state_nr-1)
	{
		cur[i][k] = 0;
		i++;
		if (i >= state_nr)
		{
			i = 0;
			++k;
			if (k > 1)
			{
				k = 0;
				incr = 0;
			}
		}
	}
	cur[i][k] += incr;
	return *this;
}

bool DFAexhaustenumAux_0::isLast()
{
	return cur_nr == max_edge_states - 1;
}

void DFAexhaustenumAux_0::reset()
{
	cur_nr = 0;
	std::fill(cur.begin(), cur.end(), std::vector<int>(2,0));

}

void DFAexhaustenumAux_0::setMaxStates(int m)
{
	if (m != state_nr)
	{
		state_nr = m;
		max_edge_states = pow(state_nr, (state_nr * 2));
		cur = std::vector<std::vector<int>>(state_nr, std::vector<int>(2, 0));
		cur_nr = 0;
	}
}


std::vector<std::vector<int>> DFAexhaustenumAux_0::toRepresentation(int nr)
{
	if (nr >= max_edge_states)
	{
		throw std::invalid_argument("Requested state is greater than maximum edge states");
	}
	cur = std::vector<std::vector<int>>(state_nr, std::vector<int>(2,0));
	div_t res;
	for(int i = 0; i < state_nr; i++)
	{
		res = div(nr, 5);
		nr = res.quot;
		cur[i][0] = res.rem;
	}
	if (res.quot != 0)
	{
		for (int j = 0; j < state_nr; j++)
		{
			res = div(nr, 5);
			nr = res.quot;
			cur[j][1] = res.rem;
		}
	}
	return cur;
}
