#pragma once

#include "InformantEnum.h"
#include <random>

class Inf_Random : public InformantEnum
{
public:
	Inf_Random();
	std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> getCur() const;
	bool isValid() const;
	void toNext();
	void reset();
	void print(std::ostream& dest, int min);
	void print_cur(std::ostream& dest);
	std::string name() { return "random"; };
	int max() { return -1; };
	bool isLast() { return false; };
private:
	int cur;
	std::vector<std::vector<int>> vec;
	std::vector<int> acc;

	std::mt19937 mt_rand;
	std::uniform_int_distribution<int> accept_gen;

	void print_single(std::ostream& dest, int i);
	void min_size(int min);
	void appendWord();


};