#ifndef _ARITHMETICAUTOMATA_HH_
# define _ARITHMETICAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	ArithmeticAutomata : public AAutomata
{
	public:
		ArithmeticAutomata();
		ArithmeticAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~ArithmeticAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
