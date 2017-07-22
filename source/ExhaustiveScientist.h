#pragma once
#include "Scientist.h"
#include "DFAenumerator.h"
#include "InformantEnum.h"

class ExhaustiveScientist : Scientist
{
public:
	ExhaustiveScientist(DFAenumerator* i);
	DFA identify(InformantEnum* const informant, const int timeout);
	~ExhaustiveScientist();
private:
	DFAenumerator* e;
};