#include "ExhaustiveScientist.h"
#include <exception>

ExhaustiveScientist::ExhaustiveScientist(DFAenumerator* e):
	e(e)
{
}

DFA ExhaustiveScientist::identify(InformantEnum* const informant, const int timeout)
{
	e->reset();
	DFA guess = e->getCur();
	bool accept = true;
	while (!e->isLast())
	{		
		for (int i = 0; i < timeout; i++)
		{
			WordIters witer = informant->getCur();
			if (guess.accepts(witer) != informant->isValid())
			{
				accept = false;
				break;
			}
			informant->toNext();
		}		
		if (accept)
		{
			return guess;
		}
		e->next(); 
		guess = e->getCur();
		accept = true;
	}
	throw std::runtime_error("No automata found. Try increasing number of states.");
}

ExhaustiveScientist::~ExhaustiveScientist()
{
	delete e;
}
