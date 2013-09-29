#ifndef _ANALEX_HH_
# define _ANALEX_HH_

#include 																<vector>
#include 																"AAutomata.hh"

class 																	Analex
{
	protected:
		std::vector<AAutomata *> 						_automata;
		std::vector<AAutomata *>:itertator 	_iter;
	public:
		Analex();
		Analex(Analex const &);
		Analex & operator=(Analex const &);
		~Analex();
		std::vector

};

#endif
