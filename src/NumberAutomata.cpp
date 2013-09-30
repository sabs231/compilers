#include 	"NumberAutomata.hh"


NumberAutomata::NumberAutomata(std::string name)
	: AAutomata(name)
{
	this->_stateNum = 2;
	this->_symbolNum = 1;
	this->_stateIndex.insert(std::pair<char, int>('A', 0));
	this->_stateIndex.insert(std::pair<char, int>('B', 1));
	this->_symbolIndex.insert(std::pair<char, int>('N', 0));
	this->_transitionTable = new t_state*[this->_stateNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
		this->_transitionTable[i] = new t_state[this->_symbolNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
	{
		for (unsigned int j = 0; j < this->_symbolNum; j++)
		{
			this->_transitionTable[i][j].name = 'B';
			this->_transitionTable[i][j].isFinal = true;
		}
	}
}

NumberAutomata::NumberAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name)
	: AAutomata(transitionTable, stateNum, symbolNum, name)
{
}

NumberAutomata::~NumberAutomata()
{
	if (this->_transitionTable)
		delete [] this->_transitionTable;
}

char NumberAutomata::simplifySymbol(char currentSymbol) const
{
	if ((currentSymbol >= '0' && currentSymbol <= '9'))
		return ('N');
	else
		return ('#');
}
