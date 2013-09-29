#include 	"NumberAutomata.hh"


NumberAutomata::NumberAutomata()
	: AAutomata()
{
	this->_stateNum = 2;
	this->_symbolNum = 10;
	this->_stateIndex.insert(std::pair<char, int>('A', 0));
	this->_stateIndex.insert(std::pair<char, int>('B', 1));
	this->_symbolIndex.insert(std::pair<char, int>('0', 0));
	this->_symbolIndex.insert(std::pair<char, int>('1', 1));
	this->_symbolIndex.insert(std::pair<char, int>('2', 2));
	this->_symbolIndex.insert(std::pair<char, int>('3', 3));
	this->_symbolIndex.insert(std::pair<char, int>('4', 4));
	this->_symbolIndex.insert(std::pair<char, int>('5', 5));
	this->_symbolIndex.insert(std::pair<char, int>('6', 6));
	this->_symbolIndex.insert(std::pair<char, int>('7', 7));
	this->_symbolIndex.insert(std::pair<char, int>('8', 8));
	this->_symbolIndex.insert(std::pair<char, int>('9', 9));
	this->_transitionTable = new t_state*[this->_stateNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
		this->_transitionTable[i] = new t_state[this->_symbolNum]; // Numbers 0 - 9
	for (unsigned int i = 0; i < this->_stateNum; i++)
	{
		for (unsigned int j = 0; j < this->_symbolNum; j++)
		{
			this->_transitionTable[i][j].name = 'B';
			if (i == this->_stateNum - 1)
				this->_transitionTable[i][j].isFinal = true;
			else
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
