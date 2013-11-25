#ifndef _IDAUTOMATA_HH_
# define _IDAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	IdAutomata : public AAutomata
{
	public:
		IdAutomata(std::string name);
		IdAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name);
		~IdAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
