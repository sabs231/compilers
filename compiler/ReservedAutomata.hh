#ifndef _RESERVEDAUTOMATA_HH_
# define _RESERVEDAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	ReservedAutomata : public AAutomata
{		
	public:
		ReservedAutomata(std::string name);
		ReservedAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name);
		~ReservedAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
