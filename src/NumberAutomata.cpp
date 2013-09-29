#include 	"NumberAutomata.hh"


NumberAutomata::NumberAutomata()
	: AAutomata()
{
	this->_stateNum = 2;
	this->_symbolNum = 10;
	this->_transitionTable = new t_state*[this->_stateNum];
	for (int i = 0; i < this->_stateNum; i++)
		this->_transitionTable[i] = new t_state[this->_symbolNum]; // Numbers 0 - 9
	for (int i = 0; i < this->_stateNum; i++)
	{
		for (int j = 0; j < this->_symbolNum; j++)
		{
			this->_transitionTable[i][j].name = 'B';
			if (i == this->_stateNum - 1)
				this->_transitionTable[i][j].isFinal = true;
			this->_transitionTable[i][j].isFinal = false;
		}
	}
}

NumberAutomata::NumberAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum)
	: AAutomata(transitionTable, stateNum, symbolNum)
{
}

NumberAutomata::~NumberAutomata()
{
	if (this->_transitionTable)
		delete [] this->_transitionTable;
}

char NumberAutomata::transition(t_state *currentState, char nextChar)
{
	// Implement this
	return ('\0');
}
