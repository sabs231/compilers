#ifndef _ANALEX_HH_
# define _ANALEX_HH_

#include 																<vector>
#include 																<string>
#include 																"AAutomata.hh"

class 																	Analex
{
	protected:
		std::vector<AAutomata *> 						_automata;
	public:
		Analex();
		Analex(Analex const &);
		Analex & operator=(Analex const &);
		~Analex();
		std::vector<AAutomata *> & getAutomata();
		int run(char *fileName);

};

#endif
