#pragma once

#include <utility>
#include <vector>
#include "InformantEnum.h"
#include <random>

class Even1s_infenum : public InformantEnum
{
public:
	Even1s_infenum();
	std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> getCur() const ;
	bool isValid() const;
	void toNext();
	void reset();
	void print(std::ostream& dest, int min);
	void print_cur(std::ostream& dest);
	std::string name() { return "even1s"; };
	int max() { return -1; };
	bool isLast() { return false; };
private:
	int cur;
	void min_size(int min);
	std::vector<int> vec;
	std::vector<int> valid;
	void print_single(std::ostream& dest, int i);
	void appendBit();

	std::mt19937 mt_rand;
	std::uniform_int_distribution<int> bit_gen;
};