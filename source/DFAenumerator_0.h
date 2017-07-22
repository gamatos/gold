#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include "DFA_0.h"


class DFAenumerator_0
{
public:
	virtual DFA_0 getCur() const = 0;
	virtual const DFAenumerator_0& next() = 0;
	virtual bool isLast() = 0;
	virtual void reset() = 0;
	virtual void setMaxStates(int i) = 0;
	virtual std::string name() = 0;
};