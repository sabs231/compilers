#ifndef _STRINGAUTOMATA_HH_
# define _STRINGAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	StringAutomata : public AAutomata
{
	public:
		StringAutomata(std::string name);
		StringAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name);
		~StringAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
