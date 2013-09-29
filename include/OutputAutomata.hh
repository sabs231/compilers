#ifndef _OUTPUTAUTOMATA_HH_
# define _OUTPUTAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	OutputAutomata : public AAutomata
{
	public:
		OutputAutomata();
		OutputAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~OutputAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
