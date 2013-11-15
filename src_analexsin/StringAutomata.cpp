#include 	"StringAutomata.hh"


StringAutomata::StringAutomata(std::string name)
	: AAutomata(name)
{
	this->_stateNum = 3;
	this->_symbolNum = 4;
	this->_stateIndex.insert(std::pair<char, int>('A', 0));
	this->_stateIndex.insert(std::pair<char, int>('B', 1));
	this->_stateIndex.insert(std::pair<char, int>('C', 2));
	this->_symbolIndex.insert(std::pair<char, int>('N', 0));
	this->_symbolIndex.insert(std::pair<char, int>('L', 1));
	this->_symbolIndex.insert(std::pair<char, int>(' ', 2));
	this->_symbolIndex.insert(std::pair<char, int>('"', 3));
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
	this->_transitionTable[0][3].name = 'B';
	this->_transitionTable[1][0].name = 'B';
	this->_transitionTable[1][1].name = 'B';
	this->_transitionTable[1][2].name = 'B';
	this->_transitionTable[1][3].name = 'C';
	this->_transitionTable[1][3].isFinal = true;
}

StringAutomata::StringAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum, std::string name)
	: AAutomata(transitionTable, stateNum, symbolNum, name)
{
}

StringAutomata::~StringAutomata()
{
	if (this->_transitionTable)
		delete [] this->_transitionTable;
}

char StringAutomata::simplifySymbol(char currentSymbol) const
{
	if ((currentSymbol >= 'a' && currentSymbol <= 'z') || (currentSymbol >= 'A' && currentSymbol <= 'Z'))
		return ('L');
	else if ((currentSymbol >= '0' && currentSymbol <= '9'))
		return ('N');
	else if (currentSymbol == '<' || currentSymbol == '>' || currentSymbol == '/' || currentSymbol == '&')
		return ('N');
	else
		return (currentSymbol);
}
