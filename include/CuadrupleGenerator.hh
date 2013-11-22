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
		std::list<std::string> Sentencia(unsigned int currentCount);
		std::list<std::string> EControl(unsigned int currentCount);
		std::list<std::string> Declaracion();
		std::list<std::string> Listid(int index, std::string idName);
		std::list<std::string> ListidP(int index, std::string idName);
		std::list<std::string> BloqueS(unsigned int currentCount);
		std::list<std::string> BloqueE(unsigned int currentCount);
		ReturnCuadrupleInfo Condicion();
		ReturnCuadrupleInfo Expresion();
		std::list<std::string> Operacion(unsigned int currentCount);
		ReturnCuadrupleInfo Operador(std::string leftOperator);
		std::list<std::string> Impresion();
		std::list<std::string> ImpresionP();
		std::list<std::string> ImpresionE();
};

#endif
