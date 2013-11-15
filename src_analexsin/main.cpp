#include <iostream>
#include "Analex.hh"
#include "Anasin.hh"

int main(int argc, char **argv){
	SymbolTable *tab = new SymbolTable();
	Analex 		analex(tab);
	Anasin		anasin(tab);

	if (argc != 2){
		std::cout << "Uso: " << argv[0] << " [file name]" << std::endl;
		return (-1);
	}
	// Run Analex
	analex.run(argv[1]);
	// Write Symbol Table
	std::cout << std::endl << "Tabla de simbolos escrita en symbolTable.txt" << std::endl;
	tab->writeToFile();
	/*	Run Anasin 	*/
	if(anasin.run(tab)){
		std::cout << "Gramática Aceptada" << std::endl;
	}else{
		std::cout << "Gramática Denegada" << std::endl;
	}
	std::cout << std::endl;
	return (0);
}
