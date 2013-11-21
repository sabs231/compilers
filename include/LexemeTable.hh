#ifndef _SYMBOLTABLE_HH_
# define _SYMBOLTABLE_HH_

# include 	<vector>
#include 	"LexemeTable.hh"
#include 	"Lexema.hh"

class 	LexemeTable{
	protected:
		std::vector<Lexema> _symTable;
		unsigned int _indexOffset;
	public:
		LexemeTable();
		LexemeTable(LexemeTable const &);
		LexemeTable & operator=(LexemeTable const &);
		~LexemeTable();
		void insert(Lexema);
		void writeToFile();
		Lexema getLexema();
		Lexema lookAheadLexema(int lookahead=0);
		int getSize();
		int getOffset();
		void resetOffset();
};

#endif
