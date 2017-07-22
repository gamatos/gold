#include "RawInformant.h"
#include <chrono>
#include <algorithm>

RawInformant::RawInformant(const std::vector<int>& acc, const std::vector<std::vector<int>>& wlist) :
	wlist(wlist),
	acc(acc),
	cur(1)
{
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> RawInformant::getCur() const
{
	return std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
		(wlist[cur - 1].begin(), wlist[cur - 1].end());
}

bool RawInformant::isValid() const
{
	return acc[cur - 1];
}

void RawInformant::toNext()
{
	++cur;
	if (cur > wlist.size())
	{
		cur = 1;
	}
}

void RawInformant::reset()
{
	cur = 1;
}

void RawInformant::print(std::ostream & dest, int min)
{
	int m = std::min(min, max());
	for (int i = 1; i <= m; i++)
	{
		print_single(dest, i);
		dest << "\n";
	}
}

void RawInformant::print_cur(std::ostream & dest)
{
	print_single(dest, cur);
}

bool RawInformant::isLast()
{
	return cur == wlist.size();
}

int RawInformant::max()
{
	return wlist.size();
}

void RawInformant::print_single(std::ostream & dest, int i)
{
	dest << acc[i - 1] << "\t";
	std::copy(wlist[i - 1].begin(), wlist[i - 1].end(), std::ostream_iterator<int>(dest));
}