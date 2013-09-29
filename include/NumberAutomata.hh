#ifndef _NUMBERAUTOMATA_HH_
# define _NUMBERAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	NumberAutomata : public AAutomata
{
	public:
		NumberAutomata();
		NumberAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~NumberAutomata();
};

#endif
