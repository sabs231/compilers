#ifndef _CUADRUPLEGEN_HH_
# define _CUADRUPLEGEN_HH_

#include "LexemeTable.hh"
#include 	<list>
#include 	<string>
#include 	<sstream>

typedef struct ReturnCuadrupleInfo{
	int Tname;
	std::list<std::string> Clist;
} ReturnCuadrupleInfo;

class CuadrupleGenerator{
	protected:
		LexemeTable *_lexTab;
		unsigned int Tcount;
	public:
		CuadrupleGenerator(LexemeTable *);
		CuadrupleGenerator(CuadrupleGenerator const &);
		CuadrupleGenerator & operator=(CuadrupleGenerator const &);
		~CuadrupleGenerator();
		
		int ParseToken(Lexema lexemaEsperado, bool checkVal);
		std::list<std::string> run(LexemeTable *);
		std::list<std::string> Sentencia(unsigned int cc);
		std::list<std::string> EControl(unsigned int cc);
		std::list<std::string> Declaracion();
		std::list<std::string> Listid(int index, std::string idName);
		std::list<std::string> ListidP(int index, std::string idName);
		std::list<std::string> BloqueS();
		std::list<std::string> BloqueE();
		ReturnCuadrupleInfo Condicion();
		std::list<std::string> Expresion();
		std::list<std::string> Aarr();
		std::list<std::string> AarrP();
		std::list<std::string> AarrP2();
		std::list<std::string> Operacion(unsigned int cc);
		std::list<std::string> Operador();
		std::list<std::string> Impresion();
		std::list<std::string> ImpresionP();
		std::list<std::string> ImpresionE();
};

#endif
