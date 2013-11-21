#ifndef _CUADRUPLEGEN_HH_
# define _CUADRUPLEGEN_HH_

#include "LexemeTable.hh"

class CuadrupleGenerator{
	protected:
		LexemeTable *_lexTab;
		unsigned int Tcount;
	public:
		CuadrupleGenerator(LexemeTable *);
		CuadrupleGenerator(CuadrupleGenerator const &);
		CuadrupleGenerator & operator=(CuadrupleGenerator const &);
		~CuadrupleGenerator();
		
		int run(LexemeTable *);
		int ParseToken(Lexema lexemaEsperado, bool checkVal);
		int Sentencia();
		int EControl();
		int Declaracion();
		int Listid(int index, std::string idName);
		int ListidP(int index, std::string idName);
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
