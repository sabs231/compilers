#ifndef _RESERVEDAUTOMATA_HH_
# define _RESERVEDAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	ReservedAutomata : public AAutomata
{
	public:
		ReservedAutomata();
		ReservedAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~ReservedAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
