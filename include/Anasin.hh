#ifndef _ANASIN_HH_
# define _ANASIN_HH_

#include "SymbolTable.hh"

class Anasin{
	protected:
		SymbolTable *_symTab;
	public:
		Anasin(SymbolTable *);
		Anasin(Anasin const &);
		Anasin & operator=(Anasin const &);
		~Anasin();
		
		int run(SymbolTable *);
		int ParseToken(Lexema lexemaEsperado, bool checkVal);
		int Sentencia();
		int EControl();
		int Declaracion();
		int Listid();
		int ListidP();
		int BloqueS();
		int BloqueE();
		int Condicion();
		int Expresion();
		int Aarr();
		int AarrP();
		int AarrP2();
		int Operacion();
		int Operador();
		int Impresion();
		int ImpresionP();
		int ImpresionE();
};

#endif
