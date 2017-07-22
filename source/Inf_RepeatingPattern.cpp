#include "Inf_RepeatingPattern.h"
#include <algorithm>

Inf_RepeatingPattern::Inf_RepeatingPattern(int pattern, int s) :
vec(),
acc()
{
	int b = 1;
	int j = 0;
	int k = 2;
	int cur_s = 1;
	int ss = s + 2;
	if (s == 0)
		++ss;
	int mask = pow(2, s) - 1;
	vec.push_back(std::vector<int>());
	acc.push_back(1);
	while (true)
	{
		if (j & k)
		{
			cur_s++;
			if (ss == cur_s)
				break;
			k <<= 1;
			j = 0;
		}
		vec.push_back(toBinary(j,cur_s));
		if (cur_s == s  && j == pattern)
		{
			acc.push_back(1);
		}
		else
		{
			acc.push_back(0);
		}
		++j;
	}
}

void Inf_RepeatingPattern::print_cur(std::ostream & dest)
{
	print_single(dest, cur);
}

void Inf_RepeatingPattern::print_single(std::ostream & dest, int i)
{
	dest << acc[i - 1] << "\t";
	std::copy(vec[i - 1].begin(), vec[i - 1].end(), std::ostream_iterator<int>(dest));
}

std::vector<int> Inf_RepeatingPattern::toBinary(int i, int s)
{
	std::vector<int> gen;
	int b = (1 << s-1);
	for(int j = 0; j < s; j++)
	{
		gen.push_back(b & i ? 1 : 0);
		b >>= 1;
	}
	return gen;
}

int Inf_RepeatingPattern::getMSB(int k)
{
	for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
	{
		if (1 << i & k)
		{
			return 1 << i;
		}
	}
}

void Inf_RepeatingPattern::print(std::ostream & dest, int min)
{
	int m = std::min(min, max());
	for (int i = 1; i <= m; i++)
	{
		print_single(dest, i);
		dest << "\n";
	}
}

void Inf_RepeatingPattern::reset()
{
	cur = 1;
}

void Inf_RepeatingPattern::toNext()
{
	++cur;
	if (cur > vec.size())
	{
		reset();
	}
}

bool Inf_RepeatingPattern::isValid() const
{
	return acc[cur - 1];
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> Inf_RepeatingPattern::getCur() const
{
	return std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
		(vec[cur - 1].begin(), vec[cur - 1].end());
}

int Inf_RepeatingPattern::max()
{
	return vec.size();
}
