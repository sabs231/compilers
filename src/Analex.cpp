#include 	<fstream>
#include 	<iostream>
#include 	"Analex.hh"
#include 	"NumberAutomata.hh"
#include 	"IdAutomata.hh"
#include 	"StringAutomata.hh"
#include	"ArithmeticAutomata.hh"
#include	"RelationalAutomata.hh"
#include	"AsignmentAutomata.hh"
#include	"PunctuationAutomata.hh"
#include	"AgrupationAutomata.hh"
#include	"OutputAutomata.hh"
#include	"ReservedAutomata.hh"

Analex::Analex()
{
	AAutomata *numbers 		= new NumberAutomata(std::string("Number"));
	AAutomata *ids 			= new IdAutomata(std::string("Id"));
	AAutomata *strings		= new StringAutomata(std::string("String"));
	AAutomata *arithmetic	= new ArithmeticAutomata(std::string("Arithmetic"));
	AAutomata *relational	= new RelationalAutomata(std::string("Relational"));
	AAutomata *asignment	= new AsignmentAutomata(std::string("Asignment"));
	AAutomata *punctuation	= new PunctuationAutomata(std::string("Punctuation"));
	AAutomata *agrupation	= new AgrupationAutomata(std::string("Agrupation"));
	AAutomata *output		= new OutputAutomata(std::string("Output"));
	AAutomata *reserved		= new ReservedAutomata(std::string("Reserved"));
	this->_automata.push_back(numbers);
	this->_automata.push_back(ids);
	this->_automata.push_back(strings);
	this->_automata.push_back(arithmetic);
	this->_automata.push_back(relational);
	this->_automata.push_back(asignment);
	this->_automata.push_back(punctuation);
	this->_automata.push_back(agrupation);
	this->_automata.push_back(output);
	this->_automata.push_back(reserved);
	
	/* XXX Testing Transition Tables, dont delete
	std::cout << "Number Automata" << std::endl;
	numbers->printTransitionTable();
	std::cout << "Id Automata" << std::endl;
	ids->printTransitionTable();
	std::cout << "String Automata" << std::endl;
	strings->printTransitionTable();
	std::cout << "Arithmetic Automata" << std::endl;
	arithmetic->printTransitionTable();
	std::cout << "Relational Automata" << std::endl;
	relational->printTransitionTable();
	std::cout << "Asignment Automata" << std::endl;
	asignment->printTransitionTable();
	std::cout << "Punctuation Automata" << std::endl;
	punctuation->printTransitionTable();
	std::cout << "Agrupation Automata" << std::endl;
	agrupation->printTransitionTable();
	std::cout << "Output Automata" << std::endl;
	output->printTransitionTable();
	std::cout << "Reserved Automata" << std::endl;
	reserved->printTransitionTable();
	*/
}

Analex::Analex(Analex const &other)
{
	this->_automata = other._automata;
}

Analex & Analex::operator=(Analex const &other)
{
	if (this != &other)
		this->_automata = other._automata;
	return (*this);
}

Analex::~Analex()
{
}

std::vector<AAutomata *> & Analex::getAutomata()
{
	return (this->_automata);
}

int Analex::run(char *fileName)
{
	std::vector<AAutomata *>::iterator 	it;
	std::ifstream 											inputRead(fileName);
	t_state 														*currentState;
	char 																currentChar;
	char 																lastChar;
	bool 																isAccepted;
	bool 																readChar;

	if (!inputRead.is_open())
	{
		std::cerr << "Unable to open file: " << fileName << std::endl;
		return (-1);
	}
	while (inputRead.good())
	{
		isAccepted = false;
		readChar = true;
		if (readChar)
		{
			inputRead.get(currentChar);
			lastChar = currentChar;
		}
		it = this->_automata.begin();
		while (it != this->_automata.end())
		{
			currentState = (*it)->getInitialState();
			while (!isAccepted)
			{
				currentState = (*it)->transition(currentState, currentChar);
				if (currentState != NULL)
				{
					if (currentState->isFinal)
					{
						inputRead.get(currentChar);
						if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n')
						{
							isAccepted = true;
							std::cout << "automata accepted" << std::endl;
						}
						else if ((*it)->transition(currentState, currentChar) == NULL)
						{
							isAccepted = true;
							readChar = false;
							std::cout << "automata accepted" << std::endl;
						}
					}
				}
				break;
			}
			if (!readChar || isAccepted)
				break;
			++it;
		}
	}
	return (0);
}
