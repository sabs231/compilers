#ifndef _ANALEX_HH_
# define _ANALEX_HH_

#include 	<vector>
#include 	<string>
#include 	"AAutomata.hh"
#include 	"LexemeTable.hh"

class 		Analex
{
	protected:
		LexemeTable 				*_symTab;
		std::vector<AAutomata *> 	_automata;
	public:
		Analex(LexemeTable *);
		Analex(Analex const &);
		Analex & operator=(Analex const &);
		~Analex();
		std::vector<AAutomata *> & getAutomata();
		int run(char *fileName);

};

#endif
