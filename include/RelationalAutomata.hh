#ifndef _RELATIONALAUTOMATA_HH_
# define _RELATIONALAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	RelationalAutomata : public AAutomata
{
	public:
		RelationalAutomata();
		RelationalAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~RelationalAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
