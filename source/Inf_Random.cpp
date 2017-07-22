#include "Inf_Random.h"
#include <chrono>
#include <algorithm>

Inf_Random::Inf_Random() :
	mt_rand(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
	accept_gen(0, 1),
	cur(0)
{
	toNext();
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> Inf_Random::getCur() const
{
	return std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
		(vec[cur-1].begin(), vec[cur-1].end());
}

bool Inf_Random::isValid() const
{
	return acc[cur-1];
}

void Inf_Random::toNext()
{
	++cur;
	if (cur > vec.size())
	{
		appendWord();
	}
}

void Inf_Random::reset()
{
	cur = 1;
}

void Inf_Random::print(std::ostream & dest, int min)
{
	min_size(min);
	for (int i = 1; i <= min; i++)
	{
		print_single(dest, i);
		dest << "\n";
	}
}

void Inf_Random::print_cur(std::ostream & dest)
{
	print_single(dest, cur);
}

void Inf_Random::print_single(std::ostream & dest, int i)
{
	dest << acc[i-1] << "\t";
	std::copy(vec[i-1].begin(), vec[i-1].end(), std::ostream_iterator<int>(dest));
}

void Inf_Random::min_size(int min)
{
	if (vec.size() < min)
	{
		int add = min - vec.size();
		for (int i = 0; i < add; i++)
		{
			appendWord();
		}
	}
}

void Inf_Random::appendWord()
{
	std::vector<int> w;

	unsigned int gen = mt_rand();
	int j = 1;
	while (j != 0)
	{
		bool b = gen & j;
		w.push_back(b);
		j <<= 1;
	}

	if (std::find(vec.begin(), vec.end(), w) != vec.end())
	{
		toNext();
		return;
	}

	vec.push_back(w);
	acc.push_back(accept_gen(mt_rand));
}
