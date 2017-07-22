#pragma once
#include <vector>
#include <utility>
#include "misc.h"

class DFA 
{
public:
	DFA(std::vector<std::vector<int>> transitions, int f);
	bool accepts(const std::vector<int> w);
	bool accepts(WordIters w);
	const std::vector<std::vector<int>>& getTransitions();
	const int getFinalStates();
	bool isMinimal();
private:
	std::vector<std::vector<int>> transitions;
	int final;
	int mask_binary;
};