#pragma once
#include <vector>

class CombGen
{
public:
	CombGen(int n, int k);
	void next();
	std::vector<int> getCur();
	bool isLast();
private:
	std::vector<int> cur;
	void genAux(int i);
	int last = false;
	int n;
	int k;
};