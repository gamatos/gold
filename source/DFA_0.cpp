#include "DFA_0.h"
#include "gvc.h"
#include <list>
#include <algorithm>
#include <bitset>

DFA_0::DFA_0(std::vector<std::vector<int>> transitions) :
	transitions(transitions),
	mask_binary((1 << transitions.size()) - 1)
{
}

int DFA_0::compatible(InformantEnum* w, int n)
{
	int final_binary_1 = 0;
	int final_binary_0 = 0;
	int state_nr = transitions.size();
	for (int i=0; i < n; i++)
	{
		WordIters wi = w->getCur();
		int cur_state = 0;
		for (std::vector<int>::const_iterator it2 = wi.first; it2 != wi.second; ++it2)
		{
			cur_state = transitions[cur_state][*it2];
		}
		int b = 1 << cur_state;
		if (w->isValid())
		{
			if (b & final_binary_0)
			{
				return -1;
			}
			final_binary_1 |= b;			
		}
		else
		{
			if (b & final_binary_1)
			{
				return -1;
			}
			final_binary_0 |= b;
		}

		w->toNext();
	}
	return final_binary_1;
}

const std::vector<std::vector<int>>& DFA_0::getTransitions()
{
	return transitions;
}
