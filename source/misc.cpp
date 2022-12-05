#include <vector>
#include <stdexcept>
#include "misc.h"

std::vector<int> strtobin(std::string s)
{
	std::vector<int> res;
	for (auto i = s.begin(); i != s.end(); i++)
	{
		if (*i == '0')
		{
			res.push_back(0);
		}
		else if (*i == '1')
		{
			res.push_back(1);
		}
		else
		{
			throw std::runtime_error("String does not contain binary number.");
		}
	}
}

int strtointbin(std::string s)
{
	int res = 0;
	int b = 1;
	for (auto i = s.rbegin(); i != s.rend(); i++)
	{
		if (*i == '0')
		{
			res &= (~b);
		}
		else if (*i == '1')
		{
			res |= b;
		}
		else
		{
			return -1;
		}
		b <<= 1;
	}
	return res;
}