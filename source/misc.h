#pragma once
#include <utility>
#include <vector>
#include <string>
typedef std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> WordIters;
std::vector<int> strtobin(std::string s);
int strtointbin(std::string s);