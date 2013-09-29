#include 	"RelationalAutomata.hh"


RelationalAutomata::RelationalAutomata()
	: AAutomata()
{
	this->_stateNum = 3;
	this->_symbolNum = 3;
	this->_stateIndex.insert(std::pair<char, int>('A', 0));
	this->_stateIndex.insert(std::pair<char, int>('B', 1));
	this->_stateIndex.insert(std::pair<char, int>('C', 2));
	this->_symbolIndex.insert(std::pair<char, int>('=', 0));
	this->_symbolIndex.insert(std::pair<char, int>('>', 1));
	this->_symbolIndex.insert(std::pair<char, int>('<', 2));

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
	this->_transitionTable[0][1].name = 'C';
	this->_transitionTable[0][1].isFinal = true;
	this->_transitionTable[0][2].name = 'C';
	this->_transitionTable[0][2].isFinal = true;
	this->_transitionTable[1][0].name = 'C';
	this->_transitionTable[1][0].isFinal = true;

}

RelationalAutomata::RelationalAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum)
	: AAutomata(transitionTable, stateNum, symbolNum)
{
}

RelationalAutomata::~RelationalAutomata()
{
	if (this->_transitionTable)
		delete [] this->_transitionTable;
}

char RelationalAutomata::simplifySymbol(char currentSymbol) const{
	return currentSymbol;
}
