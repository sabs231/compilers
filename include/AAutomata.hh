#ifndef _AAUTOMATA_HH_
# define _AAUTOMATA_HH_

# include 								<map>
# include 								<string>

typedef struct 						s_state
{
	char 										name;
	bool 										isFinal;
} 												t_state;

class 										AAutomata
{
	protected:
		t_state 							**_transitionTable;
		unsigned int 					_stateNum;
		unsigned int 					_symbolNum;
		std::map<char, int> 	_stateIndex;
		std::map<char, int> 	_symbolIndex;
		std::string						_automataName;

	public:
		AAutomata(std::string name);
		AAutomata(AAutomata const & other);
		AAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name); 
		AAutomata & operator=(AAutomata const & other);
		virtual ~AAutomata() {}
		t_state *getInitialState() const;
		unsigned int getStateNum() const;
		unsigned int getSymbolNum() const;
		int getStateIndex(char currentState) const;
		int getSymbolIndex(char currentSymbol) const;
		t_state *transition(t_state *currentState, char nextChar);
		virtual char simplifySymbol(char currentSymbol) const;
		void printTransitionTable();
		std::string getName();
};

#endif
