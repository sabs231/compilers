#ifndef _ASIGNMENTAUTOMATA_HH_
# define _ASIGNMENTAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	AsignmentAutomata : public AAutomata
{
	public:
		AsignmentAutomata();
		AsignmentAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~AsignmentAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
