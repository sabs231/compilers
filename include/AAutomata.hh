#ifndef _AAUTOMATA_HH_
# define _AAUTOMATA_HH_

typedef struct 		s_state
{
	char 						name;
	bool 						isFinal;
} 								t_state;

class 						AAutomata
{
	protected:
		t_state 			**_trasitionTable;
		unsigned int 	_stateNum;
		unsigned int 	_symbolNum;

	public:
		AAutomata();
		AAutomata(AAutomata const & other);
		AAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum); 
		AAutomata & operator=(AAutomata const & other);
		virtual ~AAutomata() {}
		char 	getInitialState() const;
		virtual char transition(t_state *currentState, char nextChar) = 0;
};

#endif
