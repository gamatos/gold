#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include "DFA.h"


class DFAenumerator
{
public:
	virtual DFA getCur() const = 0;
	virtual const DFAenumerator& next() = 0;
	virtual bool isLast() = 0;
	virtual void reset() = 0;
	virtual void setMaxStates(int i) = 0;
	virtual std::string name() = 0;
};