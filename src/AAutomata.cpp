#include 	<cstdlib>
#include 	<iostream>
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

	it = this->_symbolIndex.find(this->simplifySymbol(currentSymbol));
	if (it == this->_symbolIndex.end())
		return (-1);
	return (it->second);
}

t_state 	*AAutomata::getInitialState() const
{
	t_state 	*st = new t_state;

	st->name = 'A';
	st->isFinal = false;
	return (st);
}

char AAutomata::simplifySymbol(char currentSymbol) const
{
	return currentSymbol;
}

t_state *AAutomata::transition(t_state *currentState, char nextChar)
{
	int 	stateIndex;
	int 	symbolIndex;

	if ((stateIndex = this->getStateIndex(currentState->name)) == -1)
		return (NULL);
	if ((symbolIndex = this->getSymbolIndex(nextChar)) == -1)
		return (NULL);
	return (&this->_transitionTable[stateIndex][symbolIndex]);
}

void AAutomata::printTransitionTable()
{
	for (unsigned int i = 0; i < this->_stateNum; i++)
	{
		for (unsigned int j = 0; j < this->_symbolNum; j++)
		{
			std::cout << this->_transitionTable[i][j].name << "," << this->_transitionTable[i][j].isFinal << " ";
		}
		std::cout << std::endl;
	}
}
