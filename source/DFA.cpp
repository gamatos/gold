#include "DFA.h"
#include "gvc.h"
#include <list>
#include <algorithm>
#include <bitset>

DFA::DFA(std::vector<std::vector<int>> transitions, int final) :
	transitions(transitions),
	final(final),
	mask_binary((1 << transitions.size()) - 1)
{
}


bool DFA::accepts(const std::vector<int> w)
{
	return DFA::accepts(WordIters(w.begin(), w.end()));
}

bool DFA::accepts(WordIters w)
{
	int cur_state = 0;
	for (std::vector<int>::const_iterator it = w.first; it != w.second; ++it)
	{
		cur_state = transitions[cur_state][*it];
	}
	if ((1 << cur_state) & final)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const std::vector<std::vector<int>>& DFA::getTransitions()
{
	return transitions;
}

const int DFA::getFinalStates()
{
	return final;
}

bool DFA::isMinimal()
{
	std::list<int> p;
	std::list<int> w;

	p.push_back(final);
	p.push_back(~final & mask_binary);
	w.push_back(final);

	while (!w.empty())
	{
		int a = w.back();
		w.pop_back();
		int x = 0;
		for (int i = 0; i <= 1; i++)
		{
			int b = 1;
			for (int j = 0; j < transitions.size(); j++)
			{
				if (final & (1 << transitions[j][i]))
				{
					x |= b;
				}
				b <<= 1;
			}
			auto k = p.begin();
			while(k != p.end())
			{
				int y = *k;
				int y1 = y & x;
				int y2 = y & ~x & mask_binary;
				if (y1 && y2)
				{
					k = p.erase(k);
					p.push_front(y1);
					p.push_front(y2);
				
					auto yp = std::find(w.begin(), w.end(), y);
					if (yp != w.end())
					{
						w.erase(yp);
						w.push_back(y1);
						w.push_back(y2);
					}
					else
					{
						std::bitset<sizeof(int)> y1_bs(y1);
						std::bitset<sizeof(int)> y2_bs(y2);
						if (y1_bs.count() < y2_bs.count())
						{
							w.push_back(y1);
						}
						else
						{
							w.push_back(y2);
						}
					}
				}
				else
				{
					++k;
				}
			}
		}
	}
	for (auto i = p.begin(); i != p.end(); i++)
	{
		if (std::bitset<sizeof(int)>(*i).count() > 1)
		{
			return false;
		}
	}
	return true;
}

	


