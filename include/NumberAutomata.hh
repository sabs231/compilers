#ifndef _NUMBERAUTOMATA_HH_
# define _NUMBERAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	NumberAutomata : public AAutomata
{
	public:
		NumberAutomata(std::string name);
		NumberAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name);
		~NumberAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
