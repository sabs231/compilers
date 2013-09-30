#ifndef _SYMBOLTABLE_HH_
# define _SYMBOLTABLE_HH_

# include 																		<map>
# include 																		<string>

class 																				SymbolTable
{
	protected:
		std::multimap<std::string, std::string> 	_symTable;
	public:
		SymbolTable();
		SymbolTable(SymbolTable const &);
		SymbolTable & operator=(SymbolTable const &);
		~SymbolTable();
		void insert(std::string, std::string);
		std::string *lookup(std::string &);
		std::multimap<std::string, std::string> & getSymTable();
		void writeToFile();
};

#endif
