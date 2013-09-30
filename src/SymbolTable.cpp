#include 	"SymbolTable.hh"

SymbolTable::SymbolTable()
{
}

SymbolTable::SymbolTable(SymbolTable const &other)
{
	this->_symTable = other._symTable;
}

SymbolTable & SymbolTable::operator=(SymbolTable const &other)
{
	if (this != &other)
		this->_symTable = other._symTable;
	return (*this);
}

SymbolTable::~SymbolTable()
{
}

void SymbolTable::insert(std::string type, std::string lexeme)
{
	this->_symTable.insert(std::pair<std::string, std::string>(type, lexeme));
}

std::string *SymbolTable::lookup(std::string & type)
{
	std::string 																				*result = new std::string();
	std::multimap<std::string, std::string>::iterator 	it;
	std::pair <std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> 	ret;

	ret = this->_symTable.equal_range(type);
	for (it = ret.first; it != ret.second; ++it)
	{
		result->append(it->second);
		result->push_back(' ');
	}
	return (result);
}

std::multimap<std::string, std::string> & SymbolTable::getSymTable()
{
	return (this->_symTable);
}

void SymbolTable::writeToFile()
{
}
