#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <list>
#include <cstdlib>
#include "DFA.h"
#include "DFAenumerator.h"
#include "DFAexhaustenumAux_0.h"
#include "DFAreisenumAux_0.h"
#include "DFAreisenum_0.h"
#include "DFArenderer.h"
#include "Inf_ExistsPattern.h"
#include "InformantEnum.h"
#include "Even1s_infenum.h"
#include "Inf_Random.h"
#include "RawInformant.h"
#include "ExhaustiveScientist.h"
#include <fstream>
#include <ostream>
#include <sstream>
#include "gvc.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_thread.h"
#include "Inf_RepeatingPattern.h"
#include <boost/algorithm/string.hpp>
#include "misc.h"

enum ProgramStates
{
	START,
	ENUM
};

using namespace std;

std::string input;
bool hasinput = false;

int thread(void*a) {
	getline(std::cin, input);
	hasinput = true;
	cout << "\n";
	return 0;
}

void clean_result(DFA*& res, DFArenderer*& resrend) 
{
	if (res)
	{
		delete res;
		res = NULL;
	}
	if (resrend)
	{
		delete resrend;
		resrend = NULL;
	}
}

void close_window(SDL_Window* gWindow, SDL_Renderer* gRenderer, bool& openWindow)
{
	openWindow = false;
	if (gRenderer)
	{
		SDL_DestroyRenderer(gRenderer);
		gRenderer = NULL;
	}
	if (gWindow)
	{
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}
}

int max_states = 7;
int symbol_nr = 2;
int timeout = 25;

bool running = true;
bool openWindow = false;
bool updateGraph = false;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Surface* loadedSurface = NULL;

std::string* loaded_file = NULL;

SDL_Rect topLeftViewport;

SDL_Event e;

GVC_t *gvc = NULL;

DFAenumerator_0* en = new DFAreisenum_0(max_states, symbol_nr);
InformantEnum* inf = NULL;

DFA* res = NULL;
DFArenderer* resrend = NULL;

int conjecture()
{
	if (!inf)
	{
		cout << "Please provide an informant! Type 'informant' for more information. \n \n \n";
		return 0;
	}
	else if (!en)
	{
		cout << "Please provide a DFA enumeration! Type 'enum' for more information. \n \n \n";
		return 0;
	}
	else
	{
		Uint32 ti = SDL_GetTicks();

		inf->reset();
		en->reset();

		DFA_0 guess = en->getCur();
		bool changed = false;
		int total_tested = 0;
		int max_words = inf->max() < 0 ? timeout : min(timeout, inf->max());
		while (!en->isLast())
		{
			++total_tested;
			int f = guess.compatible(inf, max_words);
			if (f > 0)
			{
				if (res)
					delete res;
				res = new DFA(guess.getTransitions(), f);
				changed = true;
				break;
			}
			inf->reset();
			en->next();
			guess = en->getCur();
		}
		Uint32 tf = SDL_GetTicks();

		Uint32 tms = tf - ti;

		Uint32 ms = tms % 1000;
		Uint32 tsec = (tms - ms) / 1000;

		Uint32 sec = tsec % 60;
		Uint32 min = (tsec - sec) / 60;

		if (changed)
		{
			cout << "SUCCESS \n";
			cout << "Type \"dfa draw\" to open a graph of the DFA. \n \n";
		}
		else
		{
			cout << "No automata found. Try increasing number of states.  \n \n";
		}
		cout << "Tested a total of " << total_tested << " DFAs.\n";
		cout << "Ran for " << min << ":" << sec << ":" << ms << "\n \n \n";

		if (resrend)
		{
			delete resrend;
			resrend = NULL;
		}

		updateGraph = true;
		return 1;
	}
}

int load_new_file()
{
	if (loaded_file)
	{
		ifstream load(*loaded_file);

		if (!load.is_open())
		{
			cout << "Error opening file. Check filename and whether it exists. \n\n\n";
			return 0;
		}
		else
		{
			bool bad_file = false;
			string buffer;
			vector<string> load_split;
			vector<int> acc;
			vector<vector<int>> wlist;

			while (getline(load, buffer))
			{
				boost::split(load_split, buffer, [](char c) {return isspace(c); }, boost::token_compress_on);
				//load_split.erase(std::remove_if(load_split.begin(), load_split.end(),
				//	[](std::string const& s) { return s.size() == 0; }),
				//	load_split.end());

				if (load_split.size() == 2)
				{
					if (load_split[0] == "0")
					{
						acc.push_back(0);
					}
					else if (load_split[0] == "1")
					{
						acc.push_back(1);
					}
					else
					{
						bad_file = true;
					}
					if (!bad_file)
					{
						vector<int> w;

						for (string::iterator it = load_split[1].begin(); it != load_split[1].end(); it++)
						{
							if (*it == '0')
							{
								w.push_back(0);
							}
							else if (*it == '1')
							{
								w.push_back(1);
							}
							else
							{
								bad_file = true;
								break;
							}
						}
						if (!bad_file)
							wlist.push_back(w);
					}
				}
			}
			if (bad_file)
			{
				cout << "Invalid file structure. \n\n\n";
				return 0;
			}
			else
			{
				if (inf)
					delete inf;

				clean_result(res, resrend);
				close_window(gWindow, gRenderer, openWindow);

				inf = new RawInformant(acc, wlist);
				cout << "Informant loaded successfully. \n";
				return 1;
			}
		}
	}
	else
	{
		std::cout << "No file specified.";
		return 0;
	}
}

int rendergraph()
{
	if (res)
	{
		if (openWindow)
		{
			close_window(gWindow, gRenderer, openWindow);
		}

		if (updateGraph)
		{
			if (!resrend)
			{
				resrend = new DFArenderer(*res, gvc);
			}
			resrend->render("temp.png", gvc);

			if (loadedSurface)
			{
				SDL_FreeSurface(loadedSurface);
			}
			loadedSurface = IMG_Load("temp.png");
			updateGraph = false;
		}


		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);

		float sw = 1;
		float sh = 1;
		float smin = 1;

		if (loadedSurface->w > DM.w * 0.85)
			sw = (((float)DM.w) / loadedSurface->w) * 0.85;

		if (loadedSurface->h > DM.h * 0.85)
			sh = (((float)DM.h) / loadedSurface->h) * 0.85;

		smin = sw > sh ? sh : sw;

		topLeftViewport.x = 0;
		topLeftViewport.y = 0;
		topLeftViewport.w = loadedSurface->w * smin;
		topLeftViewport.h = loadedSurface->h * smin;

		gWindow = SDL_CreateWindow("", DM.w / 4, DM.h / 4,
			loadedSurface->w * smin, loadedSurface->h * smin, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		openWindow = true;

		cout << "Graph successfully rendered.\n\n\n";
		return 1;
	}
	else
	{
		cout << "A DFA is yet to be conjectured! \n \n \n";
		return 0;
	}
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
	cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << "\n";
	}

	cout <<
		R"(===============================================================================
				GOLD v. 0.1
===============================================================================
Type 'about' for a short description of the application.
Type 'help' for a list of commands
The source code can be found at https://github.com/gamatos/gold
Please submit bug reports to gabriel.matos@tecnico.ulisboa.pt or use github
-------------------------------------------------------------------------------)" "\n \n";

	gvc = gvContext();



	SDL_CreateThread(thread, "InputThread", NULL);

	while (running)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_WINDOWEVENT)
			{
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					openWindow = false;
					if (gRenderer)
					{
						SDL_DestroyRenderer(gRenderer);
						gRenderer = NULL;
					}
					if (gWindow)
					{
						SDL_DestroyWindow(gWindow);
						gWindow = NULL;
					}
					break;
				}
			}
		}

		// process input HERE
		if (hasinput)
		{
			std::vector<std::string> results;
			boost::split(results, input, [](char c) {return c == ' '; });
			/*results.erase(std::remove_if(results.begin(), results.end(),
				[](std::string const& s) { return s.size() == 0; }),
				results.end());*/
			bool valid = false;

			if (!results.empty())
			{
				if (results[0] == "about" && results.size() == 1)
				{
					cout << R"(This application illustrates the concept of a scientist as introduced by E. Mark Gold in his 1967 seminal paper "Language identification in the limit".
It attempts to identify a regular language accepting/rejecting a given finite set of data and return a deterministic finite-state automata (DFA) associated with it. 
It works by exhaustively searching all deterministic finite-state automata up to a certain number of states until it finds a suitable one.
Type 'libraries' for the list of libraries used)" "\n \n \n";
					valid = true;

				}
				if (results[0] == "libraries" && results.size() == 1)
				{
					cout << R"(SDL2 - https://www.libsdl.org/
graphviz - http://www.graphviz.org/
boost - http://www.boost.org/)" "\n \n \n";
					valid = true;

				}
				else if (results[0] == "help" && results.size() == 1)
				{
					cout << R"(
informant - shows currently selected and available informants
informant 'x' - changes informant to 'x'
print - Prints current informant data to console
identify - identify DFA associated with selected informant
dfa draw - draws last identified DFA
dfa save 'filename' - saves DFA structure in the graphviz format to the designated file
dfa savegraph 'filename' - saves DFA graph to the designated file
informant save 'filename' - saves data from current informant to the designated file, up to max_words elements
informant load 'filename' - creates informant from data in designated file
update - reloads loaded file then attempts to identify an automaton and draw its graph
enum - shows currently selected and available DFA enumerations
enum 'x' - changes enumeration to 'x'
max_words 'n' - changes maximum number of tested words to 'n'
max_states 'n' - changes maximum number of tested DFA states to 'n'
)" "\n \n \n";

					valid = true;
				}
				else if (results[0] == "enum")
				{
					if (results.size() == 1)
					{
						if (en)
						{
							cout << "Current enumeration is " << en->name() << ".\n\n";
						}
						else
						{
							cout << "There currently is no enumeration set.\n\n";
						}

						cout << R"(AVAILABLE ENUMERATIONS:
naive - naive enumeration
reis - enumeration by Rogerio Reis

Type "enum 'x'" to set the current informant to 'x'. You can also load the data from a file by typing "informant load 'filename'")" "\n\n\n";

						valid = true;
					}
					if (results.size() == 2)
					{
						bool validenum = false;
						if (results[1] == "naive")
						{
							if (en)
								delete en;
							en = new DFAexhaustenumAux_0(max_states);
							cout << "Enumeration successfully set to naive \n";
							cout << "Warning: Selected enumeration is inefficient. Use a small number of maximum states.\n\n\n";
							validenum = true;
						}
						else if (results[1] == "reis")
						{
							if (en)
								delete en;

							en = new DFAreisenum_0(max_states, symbol_nr);
							cout << "Enumeration successfully set to reis \n\n\n";
							validenum = true;
						}

						if (validenum)
						{
							en->setMaxStates(max_states);
							clean_result(res, resrend);
							close_window(gWindow, gRenderer, openWindow);
						}
						else
						{
							cout << "Requested enumeration not recognized. \n \n \n";
						}
						valid = true;
					}
				}
				else if (results[0] == "informant")
				{
					bool validinf = false;
					if (results.size() == 1)
					{
						if (inf)
						{
							cout << "Current informant is " << inf->name() << ".\n\n";
						}
						else
						{
							cout << "There currently is no informant set.\n\n";
						}

						cout << R"(AVAILABLE INFORMANTS:
even1s - informant for language that have even number of ones
random - informant based on a randomly generated sequence of 32-bit words
ex_pattern 'p' - informant for language that accepts words containing p
rep_pattern 'p' - informant for language that accepts words constructed by repeating sequence p

Type "informant 'x'" to set the current informant to 'x'. You can also load the data from a file by typing "informant 'filename'")" "\n\n\n";
						valid = true;
					}

					else if (results.size() == 2)
					{	
						if (results[1] == "even1s")
						{
							if (loaded_file)
							{
								delete loaded_file;
								loaded_file = NULL;
							}

							if (inf)
								delete inf;

							inf = new Even1s_infenum;
							validinf = true;
							cout << "Informant even1s set. \n \n \n";
						}
						else if (results[1] == "random")
						{
							if (loaded_file)
							{
								delete loaded_file;
								loaded_file = NULL;
							}
							if (inf)
								delete inf;

							inf = new Inf_Random;
							validinf = true;
							cout << "Informant random set. \n \n \n";
						}

						
						else
						{
							cout << "Requested informant not recognized. \n \n \n";
						}
						valid = true;
					}
					else if (results.size() == 3)
					{
						if (results[1] == "rep_pattern")
						{
							if (loaded_file)
							{
								delete loaded_file;
								loaded_file = NULL;
							}
							int param = strtointbin(results[2]);
							if (param < 0)
							{
								cout << "Invalid pattern. \n \n \n";
							}
							else
							{
								if (inf)
								delete inf;

								inf = new Inf_RepeatingPattern(param, results[2].size());
								validinf = true;
								cout << "Informant rep_pattern set. \n";
							}
							valid = true;
						}
						if (results[1] == "ex_pattern")
						{
							if (loaded_file)
							{
								delete loaded_file;
								loaded_file = NULL;
							}
							int param = strtointbin(results[2]);
							if (param < 0)
							{
								cout << "Invalid pattern. \n \n \n";
							}
							else
							{
								if (inf)
									delete inf;

								inf = new Inf_ExistsPattern(param, results[2].size());
								validinf = true;
								cout << "Informant ex_pattern set. \n";
							}
							valid = true;
						}
						if (results[1] == "load")
						{
							if (loaded_file)
							{
								delete loaded_file;
								loaded_file = NULL;
							}
							loaded_file = new std::string(results[2]);
							if (load_new_file())
							{
								validinf = true;
							}
							valid = true;
						}
						else if (results[1] == "save")
						{
							if (inf)
							{
								ofstream save(results[2]);
								if (!save.is_open())
								{
									cout << "Error opening file. Check filename and whether it exists. \n\n\n";
								}
								else
								{
									inf->print(save, timeout);
									cout << "Informant successfully saved to " << results[2] << ".\n";
								}
							}
							else
								cout << "No informant is currently active!\n\n\n";
							valid = true;
						}
					}	
					if (validinf)
					{
						if (inf->max() > 0)
						{
							timeout = inf->max();
							cout << "Maximum number of words set to " << inf->max() << "\n\n\n";
						}
						clean_result(res, resrend);
						close_window(gWindow, gRenderer, openWindow);
					}
				}
				else if (results[0] == "max_states")
				{
					if (results.size() == 1)
					{
						cout << "Current maximum number of states is set to " << max_states << ". \n\n\n";
					}
					if (results.size() == 2)
					{
						try {
							max_states = stoi(results[1]);
							cout << "Maximum number of states successfully set to " << max_states << ". \n\n\n";
							if (en)
							{
								en->setMaxStates(max_states);
							}
						}
						catch (std::invalid_argument& e) {
							cout << "Invalid argument. \n \n \n";
						}
						catch (std::out_of_range& e) {
							cout << "Requested number out of integer range. \n \n \n";
						}
						catch (...) {
							cout << "Unable to set maximum states. \n \n \n";
						}
					}

					valid = true;
				}
				else if (results[0] == "max_words")
				{
					if (results.size() == 1)
					{
						cout << "Current maximum test words is set to " << timeout << ". \n\n\n";
					}
					if (results.size() == 2)
					{
						try 
						{
							timeout = stoi(results[1]);
							close_window(gWindow, gRenderer, openWindow);
							clean_result(res, resrend);
							if (inf && timeout < inf->max())
							{
								cout << "Warning: Current max. nr. of words truncates informant, which has " << inf->max() << " words. \n";
							}
							cout << "Max. test words set to " << timeout << ". \n\n\n";
						}
						catch (std::invalid_argument& e) {
							cout << "Invalid argument. \n \n \n";
						}
						catch (std::out_of_range& e) {
							cout << "Requested number out of integer range. \n \n \n";
						}
						catch (...) {
							cout << "Unable to set max. test words. \n \n \n";
						}
					}

					valid = true;
				}
				else if (results[0] == "identify" && results.size() == 1)
				{
					conjecture();
					valid = true;
				}
				else if (results[0] == "update" && results.size() == 1)
				{
					if (loaded_file)
					{
						if (load_new_file())
						{
							timeout = inf->max();
							cout << "Maximum number of words set to " << inf->max() << "\n\n\n";
							if (conjecture())
							{
								rendergraph();
							}
						}
					}
					else 
					{
						cout << "Currently there is no informant supplied from a file! \n\n\n";
					}
					valid = true;
				}
				else if (results[0] == "print" && results.size() == 1)
				{
					if (inf)
					{
						inf->print(cout, timeout);
						cout << "\n \n";
					}
					else
					{
						cout << "Please provide an informant! Type 'informant' for more information. \n \n \n";
					}
					valid = true;
				}
				else if (results[0] == "dfa")
				{
					if (results.size() == 2)
					{
						if (results[1] == "draw")
						{
							rendergraph();

							valid = true;
						}
					}
					if (results.size() == 3)
					{
						if (results[1] == "savegraph")
						{
							valid = true;
							if (res)
							{
								if (!resrend)
								{
									resrend = new DFArenderer(*res, gvc);
								}

								resrend->render(results[2], gvc);
								cout << "DFA graph successfully saved to file " << results[2] << ". \n \n \n";
							}
							else
							{
								cout << "A DFA is yet to be conjectured!\n\n\n";
							}
						}
						
						if (results[1] == "save")
						{
							valid = true;
							if (res)
							{
								if (!resrend)
								{
									resrend = new DFArenderer(*res, gvc);
								}

								resrend->save(results[2], gvc);
								cout << "DFA successfully saved to file " << results[2] << ". \n \n \n";
							}
							else
							{
								cout << "A DFA is yet to be conjectured!\n\n\n";
							}
						}
					}
				}

				if (!valid)
				{
					cout << "Command '" << input << "' not recognized \n\n\n";
				}
			}
			hasinput = false;
			SDL_CreateThread(thread, "InputThread", NULL);
		}

		if (openWindow)
		{
			//Clear screen
			SDL_RenderClear(gRenderer);
			
			SDL_RenderSetViewport(gRenderer, &topLeftViewport);

			//Render texture to screen
			SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

			//Update screen
			SDL_RenderPresent(gRenderer);
		}
	}
	return 0;
}