#include 					<iostream>
#include 					"Analex.hh"

int 							main(int argc, char **argv)
{
	SymbolTable 		*tab = new SymbolTable();
	Analex 					a(tab);
	std::multimap<std::string, std::string>::iterator 	it;

	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " [file name]" << std::endl;
		return (-1);
	}
	a.run(argv[1]);
	std::cout << "Printing Symbol Table" << std::endl;
	for (it = tab->getSymTable().begin(); it != tab->getSymTable().end(); ++it)
		std::cout << it->first << " ==> " << it->second << std::endl;
	tab->writeToFile();
	return (0);
}
