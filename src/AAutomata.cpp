#include 	<cstdlib>
#include 	"AAutomata.hh"

AAutomata::AAutomata()
{
	this->_transitionTable = NULL;
	this->_stateNum = 0;
	this->_symbolNum = 0;
}

AAutomata::AAutomata(AAutomata const & other)
{
	this->_transitionTable = other._transitionTable;
	this->_stateNum = other._stateNum;
	this->_symbolNum = other._symbolNum;
}

AAutomata::AAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum)
	: _transitionTable(transitionTable), _stateNum(stateNum), _symbolNum(symbolNum)
{
}

AAutomata & AAutomata::operator=(AAutomata const & other)
{
	if (this != &other)
	{
		if (this->_transitionTable)
			delete [] this->_transitionTable;
		this->_transitionTable = other._transitionTable;
		this->_stateNum = other._stateNum;
		this->_symbolNum = other._symbolNum;
	}
	return (*this);
}

char 	AAutomata::getInitialState() const
{
	// Implement this
	return ('\0');
}
