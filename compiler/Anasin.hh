#ifndef _ANASIN_HH_
# define _ANASIN_HH_

#include "LexemeTable.hh"

class Anasin{
	protected:
		LexemeTable *_symTab;
	public:
		Anasin(LexemeTable *);
		Anasin(Anasin const &);
		Anasin & operator=(Anasin const &);
		~Anasin();
		
		int run(LexemeTable *);
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
