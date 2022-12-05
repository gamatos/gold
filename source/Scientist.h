#pragma once
#include "DFA.h"
#include "InformantEnum.h"
#include <vector>
#include <utility>

class Scientist
{
public:
	virtual DFA identify(InformantEnum* const informant, const int timeout) = 0;
};