#include 	<fstream>
#include 	<iostream>
#include 	"Analex.hh"
#include 	"NumberAutomata.hh"
#include 	"IdAutomata.hh"
#include 	"StringAutomata.hh"

Analex::Analex()
{
	AAutomata *numbers 	= new NumberAutomata();
	AAutomata *ids 		= new IdAutomata();
	AAutomata *strings	= new StringAutomata();
	this->_automata.push_back(numbers);
	this->_automata.push_back(ids);
	this->_automata.push_back(strings);
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
	std::ifstream 	inputRead(fileName);
	char 						currentChar;

	if (!inputRead.is_open())
	{
		std::cerr << "Unable to open file: " << fileName << std::endl;
		return (-1);
	}
	while (inputRead.good())
	{
		inputRead.get(currentChar);
		std::cout << currentChar << std::endl;;
	}
	return (0);
}
