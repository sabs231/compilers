#ifndef _PUNCTUATIONAUTOMATA_HH_
# define _PUNCTUATIONAUTOMATA_HH_

# include 	"AAutomata.hh"

class 	PunctuationAutomata : public AAutomata
{
	public:
		PunctuationAutomata();
		PunctuationAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum);
		~PunctuationAutomata();
		virtual char simplifySymbol(char currentSymbol) const;
};

#endif
