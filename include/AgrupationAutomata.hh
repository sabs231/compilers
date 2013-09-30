#ifndef _AGRUPATIONAUTOMATA_HH_
# define _AGRUPATIONAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	AgrupationAutomata : public AAutomata
{
	public:
		AgrupationAutomata(std::string name);
		AgrupationAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name);
		~AgrupationAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
