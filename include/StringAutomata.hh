#ifndef _STRINGAUTOMATA_HH_
# define _STRINGAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	StringAutomata : public AAutomata
{
	public:
		StringAutomata();
		StringAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~StringAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
