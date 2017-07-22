#pragma once

#include "InformantEnum.h"

class Inf_RepeatingPattern : public InformantEnum
{
public:
	Inf_RepeatingPattern(int pattern, int s);
	std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> getCur() const;
	bool isValid() const;
	void toNext();
	void reset();
	void print(std::ostream& dest, int min);
	void print_cur(std::ostream& dest);
	std::string name() { return "rep_pattern"; };
	int max();
	bool isLast() { return false; };
private:
	int cur;
	std::vector<std::vector<int>> vec;
	std::vector<int> acc;

	void print_single(std::ostream& dest, int i);
	std::vector<int> toBinary(int i, int s);
	int getMSB(int k);
};