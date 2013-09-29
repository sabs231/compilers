#include 	"PunctuationAutomata.hh"


PunctuationAutomata::PunctuationAutomata()
	: AAutomata()
{
	this->_stateNum = 2;
	this->_symbolNum = 1;
	this->_stateIndex.insert(std::pair<char, int>('A', 0));
	this->_stateIndex.insert(std::pair<char, int>('B', 1));
	this->_symbolIndex.insert(std::pair<char, int>('P', 0));

	this->_transitionTable = new t_state*[this->_stateNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
		this->_transitionTable[i] = new t_state[this->_symbolNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
	{
		for (unsigned int j = 0; j < this->_symbolNum; j++)
		{
			this->_transitionTable[i][j].name = '#';
			this->_transitionTable[i][j].isFinal = false;
		}
	}
	this->_transitionTable[0][0].name = 'B';
	this->_transitionTable[0][0].isFinal = true;
}

PunctuationAutomata::PunctuationAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum)
	: AAutomata(transitionTable, stateNum, symbolNum)
{
}

PunctuationAutomata::~PunctuationAutomata()
{
	if (this->_transitionTable)
		delete [] this->_transitionTable;
}

char PunctuationAutomata::simplifySymbol(char currentSymbol) const{
	if(currentSymbol == ';' || currentSymbol == ',')
		return 'P';
	else
		return '#';
}
