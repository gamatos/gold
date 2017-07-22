#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <iterator>
#include "misc.h"

class InformantEnum
{
public:
	virtual WordIters getCur() const = 0;
	virtual bool isValid() const = 0;
	virtual void toNext() = 0;
	virtual void reset() = 0;
	virtual int max() = 0;
	virtual void print(std::ostream& dest, int min) = 0;
	virtual void print_cur(std::ostream& dest) = 0;
	virtual bool isLast() = 0;
	virtual std::string name() = 0;
};