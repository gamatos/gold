#pragma once

#include "DFA.h"
#include "gvc.h"

class DFArenderer
{
public:
	DFArenderer(DFA d, GVC_t* gv);
	int render(std::string filename, GVC_t* gvc);
	int save(std::string filename, GVC_t* gvc);
private:
	Agraph_t* graph;
	std::vector<Agnode_t*> nodes;
	std::vector<Agedge_t*> edges;
};