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
	this->_stateIndex = other._stateIndex;
	this->_symbolIndex = other._symbolIndex;
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
		this->_stateIndex = other._stateIndex;
		this->_symbolIndex = other._symbolIndex;
	}
	return (*this);
}

unsigned int AAutomata::getStateNum() const
{
	return (this->_stateNum);
}

unsigned int AAutomata::getSymbolNum() const
{
	return (this->_symbolNum);
}

int AAutomata::getStateIndex(char currentState) const
{
	std::map<char, int>::const_iterator 	it;

	it = this->_stateIndex.find(currentState);
	if (it == this->_stateIndex.end())
		return (-1);
	return (it->second);
}

int AAutomata::getSymbolIndex(char currentSymbol) const
{
	std::map<char, int>::const_iterator 	it;

	it = this->_symbolIndex.find(currentSymbol);
	if (it == this->_symbolIndex.end())
		return (-1);
	return (it->second);
}

t_state 	*AAutomata::getInitialState() const
{
	if (this->_transitionTable)
		return (&this->_transitionTable[0][0]);
}
