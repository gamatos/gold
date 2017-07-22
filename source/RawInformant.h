#pragma once

#include "InformantEnum.h"
#include <random>

class RawInformant : public InformantEnum
{
public:
	RawInformant(const std::vector<int>& acc, const std::vector<std::vector<int>>& wlist);
	std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> getCur() const;
	bool isValid() const;
	void toNext();
	void reset();
	void print(std::ostream& dest, int min);
	void print_cur(std::ostream& dest);
	std::string name() { return "loaded"; };
	bool isLast();
	int max();
private:
	int cur;
	std::vector<std::vector<int>> wlist;
	std::vector<int> acc;
	
	void print_single(std::ostream& dest, int i);
};