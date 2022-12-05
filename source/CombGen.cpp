#include "CombGen.h"

CombGen::CombGen(int n, int k) :
	n(n),
	k(k)
{
	for (int j = 0; j < k; j++)
	{
		cur.push_back(j);
	}
}

void CombGen::next()
{
	if (!last)
	{
		++cur[k - 1];
		if (cur[k - 1] >= n && k > 1)
		{
			genAux(k - 2);
		}
	}
}

std::vector<int> CombGen::getCur()
{
	return cur;
}

bool CombGen::isLast()
{
	return last;
}

void CombGen::genAux(int i)
{
	
	if (cur[i] + 1 != cur[i + 1])
	{
		++cur[i];
		for (int j = i; i < k; i++)
		{
			cur[i] = cur[i - 1] + 1;
		}
	}
	else
	{
		if (i == 0)
		{
			last = true;
		}
	}
}
