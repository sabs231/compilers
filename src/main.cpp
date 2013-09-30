#include 					<iostream>
#include 					"Analex.hh"

int 							main(int argc, char **argv)
{
	SymbolTable 		*tab = new SymbolTable();
	Analex 					a(tab);
	std::string 		automata("Number");
	std::multimap<std::string, std::string>::iterator 	it;

	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " [file name]" << std::endl;
		return (-1);
	}
	a.run(argv[1]);
	std::cout << "Symbol Table written to symbolTable.txt" << std::endl;
	tab->writeToFile();
	return (0);
}
