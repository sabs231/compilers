#include 	"IdAutomata.hh"


IdAutomata::IdAutomata()
	: AAutomata()
{
	this->_stateNum = 2;
	this->_symbolNum = 2;
	this->_stateIndex.insert(std::pair<char, int>('A', 0));
	this->_stateIndex.insert(std::pair<char, int>('B', 1));
	this->_symbolIndex.insert(std::pair<char, int>('N', 0));
	this->_symbolIndex.insert(std::pair<char, int>('L', 1));

	this->_transitionTable = new t_state*[this->_stateNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
		this->_transitionTable[i] = new t_state[this->_symbolNum];
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
	this->_transitionTable[0][0].name = '#';
}

IdAutomata::IdAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum)
	: AAutomata(transitionTable, stateNum, symbolNum)
{
}

IdAutomata::~IdAutomata()
{
	if (this->_transitionTable)
		delete [] this->_transitionTable;
}

char IdAutomata::simplifySymbol(char currentSymbol) const{
	if((currentSymbol >= 'a' && currentSymbol <= 'z') || (currentSymbol >= 'A' && currentSymbol <= 'Z')){
		return 'L';
	}else if((currentSymbol >= '0' && currentSymbol <= '9') ){
		return 'N';
	}else{
		return '#';
	}
}
