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
	}
	return (*this);
}

char 	AAutomata::getInitialState() const
{
}
