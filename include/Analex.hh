#ifndef _ANALEX_HH_
# define _ANALEX_HH_

#include 																<vector>
#include 																<string>
#include 																"AAutomata.hh"
#include 																"SymbolTable.hh"

class 																	Analex
{
	protected:
		SymbolTable 												*_symTab;
		std::vector<AAutomata *> 						_automata;
	public:
		Analex(SymbolTable *);
		Analex(Analex const &);
		Analex & operator=(Analex const &);
		~Analex();
		std::vector<AAutomata *> & getAutomata();
		int run(char *fileName);

};

#endif
