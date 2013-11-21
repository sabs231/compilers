#include 	<iostream>
#include 	"CuadrupleGenerator.hh"
#define		DEBUG	0

CuadrupleGenerator::CuadrupleGenerator(LexemeTable *symTab): _lexTab(symTab){
}

CuadrupleGenerator::CuadrupleGenerator(CuadrupleGenerator const &other){
	this->_lexTab = other._lexTab;
}

CuadrupleGenerator & CuadrupleGenerator::operator=(CuadrupleGenerator const &other){
	if (this != &other)
		this->_lexTab = other._lexTab;
	return (*this);
}

CuadrupleGenerator::~CuadrupleGenerator(){
}

int CuadrupleGenerator::run(LexemeTable *lexTab){
	this->_lexTab = lexTab;
	if(this->_lexTab == NULL){
		return(0);
	}
	std::cout << std::endl << "-- Iniciando Generador de Cuádruplos --" << std::endl << std::endl;
	this->_lexTab->resetOffset();
	return Sentencia();
}

int CuadrupleGenerator::ParseToken(Lexema lexemaEsperado, bool checkVal){
	Lexema nextLexema = this->_lexTab->getLexema();
	if(nextLexema._tipo == lexemaEsperado._tipo){
		if(checkVal){
			if(nextLexema._valor == lexemaEsperado._valor){
				return 1;
			}
		}else{
			return 1;
		}
	}
	return 0;
}

int CuadrupleGenerator::Sentencia(){
	int countCuadruples = 0;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && (nextLexema._valor == "while" || nextLexema._valor == "if")){
		// 01) Sentencia ->	EControl Sentencia
		countCuadruples += EControl();
		countCuadruples += Sentencia();	
	}else if(nextLexema._tipo == "Id"){
		// 02) Sentencia ->	Operacion Sentencia 
		countCuadruples += Operacion();
		countCuadruples += Sentencia();
	}else if(nextLexema._tipo == "Reserved" && (nextLexema._valor == "arr" || nextLexema._valor == "count")){
		// 03) Sentencia ->	Declaracion Sentencia
		countCuadruples += Declaracion();
		countCuadruples += Sentencia();
	}else if(nextLexema._tipo == "Output"){
		// 04) Sentencia ->	Impresión Sentencia
		countCuadruples += Impresion();
		countCuadruples += Sentencia();
	}else if(nextLexema._tipo == "Agrupation" && nextLexema._valor == "}"){
		// Es la derivación a nada
	}else if(nextLexema._tipo == "$"){
		// Ya terminé :)
	}
	return countCuadruples;
}

int CuadrupleGenerator::EControl(){
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "while"){
		// 06) EControl    ->	while(Condicion)BloqueS
		ParseToken(Lexema("Reserved","while"),true);
		ParseToken(Lexema("Agrupation","("),true);
		Condicion();
		ParseToken(Lexema("Agrupation",")"),true);
		BloqueS();
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "if"){
		// 07) EControl    ->	if(Condicion)BloqueS BloqueE
		ParseToken(Lexema("Reserved","if"),true);
		ParseToken(Lexema("Agrupation","("),true);
		Condicion();
		ParseToken(Lexema("Agrupation",")"),true);
		BloqueS();
		BloqueE();
	}
	return 1;
}

int CuadrupleGenerator::Declaracion(){
	int countCuadruples = 0;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "arr"){
		// 08) Declaracion->	arr id = [Listid nil];
		Lexema larr			= this->_lexTab->getLexema();
		Lexema lid 			= this->_lexTab->getLexema();
		Lexema lasignment	= this->_lexTab->getLexema();
		Lexema lAgrupationO	= this->_lexTab->getLexema();
		countCuadruples 	+= Listid(0, lid._valor);
		Lexema lnil			= this->_lexTab->getLexema();
		Lexema lAgrupationC	= this->_lexTab->getLexema();
		Lexema lPunctuation	= this->_lexTab->getLexema();
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "count"){
		// 09) Declaracion->	count id = number;
		// (=, contador, 0, T7)
		Lexema lCount		= this->_lexTab->getLexema();
		Lexema lid 			= this->_lexTab->getLexema();
		Lexema lasignment	= this->_lexTab->getLexema();
		Lexema lnumber		= this->_lexTab->getLexema();
		Lexema lpunctuation = this->_lexTab->getLexema();
		std::cout << "(=," << lid._valor << "," << lnumber._valor << ",T#)" << std::endl;
		countCuadruples = 1;
	}
	return countCuadruples;
}

int CuadrupleGenerator::Listid(int index, std::string idName){
	int countCuadruples = 0;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Number"){
		//11) Listid -> number ListidP
		// (=, a[0], 1, T1)
		Lexema lnumber	= this->_lexTab->getLexema();
		std::cout << "(=," << idName << "[" << index << "]," << lnumber._valor << ",T#)" << std::endl;
		countCuadruples++;
		countCuadruples += ListidP(index+1, idName);
	}else if(nextLexema._tipo == "String"){
		//10) Listid -> string ListidP
		// (=, a[0], "string", T1)
		Lexema lString	= this->_lexTab->getLexema();
		std::cout << "(=," << idName << "[" << index << "],\"" << lString._valor << "\",T#)" << std::endl;
		countCuadruples++;
		countCuadruples += ListidP(index+1, idName);		
	}
	return countCuadruples;
}

int CuadrupleGenerator::ListidP(int index, std::string idName){
	int countCuadruples = 0;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Punctuation" && nextLexema._valor == ","){
		//12) ListidP -> , Listid
		this->_lexTab->getLexema();
		countCuadruples += Listid(index, idName);
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "nil"){
		//13) ListidP -> €
		// No hago nada
	}
	return countCuadruples;
}

int CuadrupleGenerator::BloqueS(){
	// 14) BloqueS -> {Sentencia}
	ParseToken(Lexema("Agrupation","{"),true);
	Sentencia();
	ParseToken(Lexema("Agrupation","}"),true);
	return 1;
}

int CuadrupleGenerator::BloqueE(){
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "else"){
		// 15) BloqueE -> else BloqueS
		ParseToken(Lexema("Reserved","else"),true);
		BloqueS();
	}else if(nextLexema._tipo == "id" ||
			nextLexema._tipo == "Output" ||
			(nextLexema._tipo == "Agrupation" && nextLexema._valor == "}") ||
			(nextLexema._tipo == "Reserved" && nextLexema._valor == "while") ||
			(nextLexema._tipo == "Reserved" && nextLexema._valor == "if") ||
			(nextLexema._tipo == "Reserved" && nextLexema._valor == "arr") ||
			(nextLexema._tipo == "Reserved" && nextLexema._valor == "count")||
			nextLexema._tipo == "$"){
		// 16) BloqueE -> €
		// No hago nada
	}else{
		std::cout << "Error sintáctico, se esperaba : else, id, }, output, while, if, arr, count y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_lexTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int CuadrupleGenerator::Condicion(){
	// 17) Condicion -> Expresion relational Expresion
	Expresion();
	ParseToken(Lexema("Relational",""),false);
	Expresion();
	return 1;
}

int CuadrupleGenerator::Expresion(){
	Lexema nextLexema 		= this->_lexTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_lexTab->lookAheadLexema(1);
	if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 20) Expresion ->	Aarr Operador
			Aarr();
			Operador();
		}else{
			// 18) Expresion -> id Operador
			ParseToken(Lexema("Id",""),false);
			Operador();
		}
	}else if(nextLexema._tipo == "Number"){
		// 19) Expresion -> number Operador
		ParseToken(Lexema("Number",""),false);
		Operador();
	}else{
		std::cout << "Error sintáctico, se esperaba : Id, number y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_lexTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int CuadrupleGenerator::Aarr(){
	// 21) Aarr -> id AarrP
	ParseToken(Lexema("Id",""),false);
	AarrP();
	return 1;
}

int CuadrupleGenerator::AarrP(){
	// 22) AarrP -> [ AarrP2
	ParseToken(Lexema("Agrupation","["),true);
	AarrP2();
	return 1;
}

int CuadrupleGenerator::AarrP2(){
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Id"){
		// 23) AarrP2 -> id ]
		ParseToken(Lexema("Id",""),false);
		ParseToken(Lexema("Agrupation","]"),true);
	}else if(nextLexema._tipo == "Number"){
		// 24) AarrP2 -> number ]
		ParseToken(Lexema("Number",""),false);
		ParseToken(Lexema("Agrupation","]"),true);
	}else{
		std::cout << "Error sintáctico, se esperaba : Id, Number y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_lexTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int CuadrupleGenerator::Operacion(){
	Lexema nextLexema 		= this->_lexTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_lexTab->lookAheadLexema(1);
	if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 26) Operacion -> Aarr=Expresion;
			Aarr();
			ParseToken(Lexema("Asignment",""),false);
			Expresion();
			ParseToken(Lexema("Punctuation",";"),true);
		}else{
			// 25) Operacion -> id=Expresion;
			ParseToken(Lexema("Id",""),false);
			ParseToken(Lexema("Asignment",""),false);
			Expresion();
			ParseToken(Lexema("Punctuation",";"),true);
		}
	}else{
		std::cout << "Error sintáctico, se esperaba : Id y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_lexTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int CuadrupleGenerator::Operador(){
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Arithmetic"){
		// 27) Operador  -> arithmetic Expresion
		ParseToken(Lexema("Arithmetic",""),false);
		Expresion();
	}else if(nextLexema._tipo == "Relational" ||
			(nextLexema._tipo == "Agrupation" && nextLexema._valor == ")") ||
			(nextLexema._tipo == "Punctuation" && nextLexema._valor == ";")){
		// 28) Operador  -> €
		// No hago nada
	}else{
		std::cout << "Error sintáctico, se esperaba : Arithmetic, Relational, ) o ; y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_lexTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int CuadrupleGenerator::Impresion(){
	// 29) Impresion -> output ImpresionP
	ParseToken(Lexema("Output",""),false);
	ImpresionP();
	return 1;
}

int CuadrupleGenerator::ImpresionP(){
	Lexema nextLexema 		= this->_lexTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_lexTab->lookAheadLexema(1);
	if(nextLexema._tipo == "String"){
		// 32) ImpresionP ->	string ImpresionE
		ParseToken(Lexema("String",""),false);
		ImpresionE();
	}else if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 30) ImpresionP ->	Aarr ImpresionE
			Aarr();
			ImpresionE();
		}else{
			// 31) ImpresionP ->	id ImpresionE
			ParseToken(Lexema("Id",""),false);
			ImpresionE();
		}
	}else {
		std::cout << "Error sintáctico, se esperaba : Id, String y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_lexTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int CuadrupleGenerator::ImpresionE(){
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Punctuation" && nextLexema._valor == ";"){
		// 33) ImpresionE-> ;
		ParseToken(Lexema("Punctuation",";"),true);
	}else if(nextLexema._tipo == "Output"){
		// 34) ImpresionE-> output;
		ParseToken(Lexema("Output",""),false);
		ParseToken(Lexema("Punctuation",";"),true);
	}else{
		std::cout << "Error sintáctico, se esperaba ; output y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_lexTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}





