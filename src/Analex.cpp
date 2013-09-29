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

Analex::Analex()
{
	AAutomata *numbers 		= new NumberAutomata();
	AAutomata *ids 			= new IdAutomata();
	AAutomata *strings		= new StringAutomata();
	AAutomata *arithmetic	= new ArithmeticAutomata();
	AAutomata *relational	= new RelationalAutomata();
	AAutomata *asignment	= new AsignmentAutomata();
	AAutomata *punctuation	= new PunctuationAutomata();
	AAutomata *agrupation	= new AgrupationAutomata();
	AAutomata *output		= new OutputAutomata();
	_automata.push_back(numbers);
	_automata.push_back(ids);
	_automata.push_back(strings);
	_automata.push_back(arithmetic);
	_automata.push_back(relational);
	_automata.push_back(asignment);
	_automata.push_back(punctuation);
	_automata.push_back(agrupation);
	_automata.push_back(output);
	
	// Delete after finishing Automatas
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
