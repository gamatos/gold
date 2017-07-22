#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include "DFAenumerator_0.h"


class DFAexhaustenumAux_0 : public DFAenumerator_0
{
	public:
		DFAexhaustenumAux_0(int state_nr);
		DFAexhaustenumAux_0(const DFAexhaustenumAux_0 & copy);

		DFAexhaustenumAux_0& operator=(const DFAexhaustenumAux_0 & rhs);

		DFA_0 getCur() const;
		const DFAexhaustenumAux_0& next();

		bool isLast();

		void reset();

		void setMaxStates(int m);


		static DFAexhaustenumAux_0 get(const int statenr);

		std::string name() { return "naive"; };

	private:
		int state_nr;
		int max_edge_states;
		std::vector<std::vector<int>> cur;
		int cur_nr = 0;
		
		std::vector<std::vector<int>> toRepresentation(int i);

		int base() const {
			return state_nr-1;
		}
	};