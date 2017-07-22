#pragma once
#include <vector>
#include <utility>
#include "misc.h"
#include "InformantEnum.h"

class DFA_0
{
public:
	DFA_0(std::vector<std::vector<int>> transitions);
	int compatible(InformantEnum* w, int n);
	const std::vector<std::vector<int>>& getTransitions();
private:
	std::vector<std::vector<int>> transitions;
	int mask_binary;
};