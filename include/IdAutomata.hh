#ifndef _IDAUTOMATA_HH_
# define _IDAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	IdAutomata : public AAutomata
{
	public:
		IdAutomata();
		IdAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~IdAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
