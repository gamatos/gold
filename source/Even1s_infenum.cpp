#include "Even1s_infenum.h"
#include <cstdlib>
#include <chrono>

using namespace std;

Even1s_infenum::Even1s_infenum() :
	cur (0),
	mt_rand(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
	bit_gen(0, 1)
{
	valid.push_back(1);
}

pair<vector<int>::const_iterator, vector<int>::const_iterator> Even1s_infenum::getCur() const
{
	return pair<vector<int>::const_iterator, vector<int>::const_iterator>(vec.begin(), vec.begin() + cur);
}

bool Even1s_infenum::isValid() const
{
	return valid[cur];
}

void Even1s_infenum::reset()
{
	cur = 0;
}

void Even1s_infenum::print_cur(std::ostream& dest)
{
	print_single(dest, cur);
}

void Even1s_infenum::min_size(int min)
{
	if (vec.size() < min)
	{
		int add = min - vec.size();
		for (int i = 0; i < add; i++)
		{
			appendBit();
		}
	}
}

void Even1s_infenum::print(std::ostream& dest, int min)
{
	min_size(min);
	for (int i = 0; i <= min; i++)
	{
		print_single(dest, i);
		dest << "\n";
	}
}


void Even1s_infenum::print_single(std::ostream& dest, int i)
{
	dest << valid[i] << "\t";
	std::copy(vec.begin(), vec.begin() + i, std::ostream_iterator<int>(dest));
}

void Even1s_infenum::appendBit()
{
	int b = bit_gen(mt_rand);
	valid.push_back(valid.back() != b);
	vec.push_back(b);
}

void Even1s_infenum::toNext()
{
	++cur;
	if (vec.size() < cur)
	{
		appendBit();
	}
}

