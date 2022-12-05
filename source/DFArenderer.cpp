#include "DFArenderer.h"
#include <sstream>
#include <iostream>

DFArenderer::DFArenderer(DFA d, GVC_t* gvc)
{
	const std::vector<std::vector<int>>& transitions = d.getTransitions();
	int fstates = d.getFinalStates();

	Agdesc_t dir = { 1, 0, 0, 1 };

	graph = agopen("dfa", dir, 0);
	//agattr(graph, AGRAPH, "overlap", "false");
	//agattr(graph, AGRAPH, "splines", "true");
	agattr(graph, AGEDGE, "label", "");
	agattr(graph, AGNODE, "shape", "circle");

	Agnode_t* init = agnode(graph, "init", 1);
	agset(init, "shape", "point");

	int nr_of_nodes = transitions.size();
	std::string nname = "node";

	for (int i = 0; i < nr_of_nodes; i++)
	{
		char c[8];
		snprintf(c, 8, "%d", i);
		Agnode_t* node = agnode(graph, c, 1);
		nodes.push_back(node);
	}

	Agedge_t* init_edge = agedge(graph, init, nodes[0], "e0", 1);

	for (int i = 0; i < nr_of_nodes; i++)
	{
		for (int j = 0; j < transitions[i].size(); j++)
		{
			int target = transitions[i][j];
			char elabel[8];
			char ename[32];
			snprintf(elabel, 8, "%d", j);
			snprintf(ename, 32, "edge_%d_%d", i, j);
			Agedge_t* edge = agedge(graph, nodes[i], nodes[target], ename, 1);
			agset(edge, "label", elabel);
			edges.push_back(edge);
		}
	}

	int b = 1;
	for (int i = 0; i < transitions.size(); i++)
	{
		if (b & fstates)
		{
			agset(nodes[i], "shape", "doublecircle");
		}
		b <<= 1;
	}

	gvLayout(gvc, graph, "dot");
}

int DFArenderer::render(std::string filename, GVC_t* gvc)
{
	return gvRenderFilename(gvc, graph, "png", filename.c_str());
}

int DFArenderer::save(std::string filename, GVC_t* gvc)
{
	return gvRenderFilename(gvc, graph, "gv", filename.c_str());
}
