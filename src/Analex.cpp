#include 	"Analex.hh"
#include 	"NumberAutomata.hh"

Analex::Analex()
{
	AAutomata *numbers = new NumberAutomata();
	_automata.push_back(numbers);
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
