#ifndef _SYMBOLTABLE_HH_
# define _SYMBOLTABLE_HH_

# include 	<vector>
#include 	"SymbolTable.hh"
#include 	"Lexema.hh"

class 	SymbolTable{
	protected:
		std::vector<Lexema> _symTable;
		unsigned int _indexOffset;
	public:
		SymbolTable();
		SymbolTable(SymbolTable const &);
		SymbolTable & operator=(SymbolTable const &);
		~SymbolTable();
		void insert(Lexema);
		void writeToFile();
		Lexema getLexema();
		Lexema lookAheadLexema(int lookahead=0);
		void offsetBack();
		int getSize();
		int getOffset();
};

#endif
