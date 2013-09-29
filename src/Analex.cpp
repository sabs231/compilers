#include 	"Analex.hh"
#include 	"NumberAutomata.hh"
#include 	"IdAutomata.hh"
#include 	"StringAutomata.hh"

Analex::Analex()
{
	AAutomata *numbers 	= new NumberAutomata();
	AAutomata *ids 		= new IdAutomata();
	AAutomata *strings	= new IdAutomata();
	_automata.push_back(numbers);
	_automata.push_back(ids);
	_automata.push_back(strings);
}

Analex::Analex(Analex const &other)
{
	this->_automata = other._automata;
}

Analex & Analex::operator=(Analex const &other)
{
	if (this != &other)
	{
		this->_automata = other._automata;
	}
	return (*this);
}

Analex::~Analex()
{
}

std::vector<AAutomata *> & Analex::getAutomata()
{
	return (this->_automata);
}
