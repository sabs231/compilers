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

Analex::Analex(SymbolTable *symTab)
	: _symTab(symTab)
{
	AAutomata *numbers 		= new NumberAutomata(std::string("Number"));
	AAutomata *reserved		= new ReservedAutomata(std::string("Reserved"));
	AAutomata *ids 			= new IdAutomata(std::string("Id"));
	AAutomata *strings		= new StringAutomata(std::string("String"));
	AAutomata *arithmetic	= new ArithmeticAutomata(std::string("Arithmetic"));
	AAutomata *relational	= new RelationalAutomata(std::string("Relational"));
	AAutomata *asignment	= new AsignmentAutomata(std::string("Asignment"));
	AAutomata *punctuation	= new PunctuationAutomata(std::string("Punctuation"));
	AAutomata *agrupation	= new AgrupationAutomata(std::string("Agrupation"));
	AAutomata *output		= new OutputAutomata(std::string("Output"));

	this->_automata.push_back(numbers);
	this->_automata.push_back(reserved);
	this->_automata.push_back(ids);
	this->_automata.push_back(strings);
	this->_automata.push_back(arithmetic);
	this->_automata.push_back(relational);
	this->_automata.push_back(asignment);
	this->_automata.push_back(punctuation);
	this->_automata.push_back(agrupation);
	this->_automata.push_back(output);
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
	std::ifstream 											inputRead(fileName);
	char 																currentChar;
	char 																nextChar;
	bool																accepted = false;
	t_state*														currentState;
	t_state*														nextState;
	std::streampos											lastPosition;
	std::streampos											LAPosition;
	std::string 												lexeme;
	std::vector<AAutomata *>::iterator 	it;

	if (!inputRead.is_open())
	{
		std::cerr << "Unable to open file: " << fileName << std::endl;
		return (-1);
	}
	while (inputRead.good())
	{
		lastPosition = inputRead.tellg();
		it = this->_automata.begin();
		while (it != this->_automata.end() && inputRead.good())
		{
			currentState = (*it)->getInitialState();
			while (inputRead.good())
			{
				inputRead.get(currentChar);
				lexeme += currentChar;
				currentState = (*it)->transition(currentState, currentChar);
				if (currentState != NULL && currentState->isFinal)
				{
					// Lookahead
					LAPosition = inputRead.tellg();
					inputRead.get(nextChar);
					nextState = (*it)->transition(currentState, nextChar);
					inputRead.seekg (LAPosition);
					if (nextState == NULL)
					{
						// Finish
						std::cout << lexeme << " - Aceptado para el automata " << (*it)->getName() << std::endl;
						this->_symTab->insert((*it)->getName(), lexeme);
						lastPosition = inputRead.tellg();
						std::cout << "LEXEME " 
											<< lexeme 
											<< " ACCEPTED " 
											<< (*it)->getName() 
											<< " AUTOMATA" << std::endl;
						it = this->_automata.begin();
						lexeme.erase();
						accepted = true;
						break;
					}
				}
				else if (currentState == NULL)
				{
					// NULL, Check with next Automata
					inputRead.seekg(lastPosition);
					lexeme.erase();
					break;
				}
			}
			if (!accepted)
				++it;
			else
				accepted = false;
		}
		if (inputRead.good())
			inputRead.get(currentChar);
	}
	return (0);
}
