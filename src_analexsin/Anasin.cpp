#include 	<iostream>
#include 	"Anasin.hh"
#define		DEBUG	0

Anasin::Anasin(LexemeTable *symTab): _symTab(symTab){
}

Anasin::Anasin(Anasin const &other){
	this->_symTab = other._symTab;
}

Anasin & Anasin::operator=(Anasin const &other){
	if (this != &other)
		this->_symTab = other._symTab;
	return (*this);
}

Anasin::~Anasin(){
}

int Anasin::run(LexemeTable *symTab){
	this->_symTab = symTab;
	if(this->_symTab == NULL){
		return(0);
	}
	std::cout << std::endl << "-- Iniciando Análisis Sintáctico --" << std::endl << std::endl;
	return Sentencia();
}

int Anasin::ParseToken(Lexema lexemaEsperado, bool checkVal){
	Lexema nextLexema = this->_symTab->getLexema();
	if(nextLexema._tipo == lexemaEsperado._tipo){
		if(checkVal){
			if(nextLexema._valor == lexemaEsperado._valor){
				return 1;
			}
		}else{
			return 1;
		}
	}
	if(checkVal){
		std::cout << "Error sintáctico, se esperaba : " << lexemaEsperado._tipo << " ("<< lexemaEsperado._valor <<") y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
	}else{
		std::cout << "Error sintáctico, se esperaba :" << lexemaEsperado._tipo << " y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
	}
	return 0;
}

int Anasin::Sentencia(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Id"){
		// 02) Sentencia ->	Operacion Sentencia 
		if(!Operacion()) return 0;
		if(!Sentencia()) return 0;
	}else if(nextLexema._tipo == "Output"){
		// 04) Sentencia ->	Impresión Sentencia
		if(!Impresion()) return 0;
		if(!Sentencia()) return 0;
	}else if(nextLexema._tipo == "Reserved" && (nextLexema._valor == "while" || nextLexema._valor == "if")){
		// 01) Sentencia ->	EControl Sentencia
		if(!EControl()) return 0;
		if(!Sentencia()) return 0;	
	}else if(nextLexema._tipo == "Reserved" && (nextLexema._valor == "arr" || nextLexema._valor == "count")){
		// 03) Sentencia ->	Declaracion Sentencia
		if(!Declaracion()) return 0;
		if(!Sentencia()) return 0;
	}else if(nextLexema._tipo == "Agrupation" && nextLexema._valor == "}"){
		// Es la derivación a nada
	}else if(nextLexema._tipo == "$"){
		// Ya terminé :)
	}else{
		std::cout << "Error sintáctico, se esperaba : Id,},output,while,if,arr,count,$ y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::EControl(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "while"){
		// 06) EControl    ->	while(Condicion)BloqueS
		if(!ParseToken(Lexema("Reserved","while"),true)) return 0;
		if(!ParseToken(Lexema("Agrupation","("),true)) return 0;
		if(!Condicion()) return 0;
		if(!ParseToken(Lexema("Agrupation",")"),true)) return 0;
		if(!BloqueS()) return 0;
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "if"){
		// 07) EControl    ->	if(Condicion)BloqueS BloqueE
		if(!ParseToken(Lexema("Reserved","if"),true)) return 0;
		if(!ParseToken(Lexema("Agrupation","("),true)) return 0;
		if(!Condicion()) return 0;
		if(!ParseToken(Lexema("Agrupation",")"),true)) return 0;
		if(!BloqueS()) return 0;
		if(!BloqueE()) return 0;
	}else{
		std::cout << "Error sintáctico, se esperaba : while, if y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::Declaracion(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "arr"){
		// 08) Declaracion->	arr id = [Listid nil];
		if(!ParseToken(Lexema("Reserved","arr"),true)) return 0;
		if(!ParseToken(Lexema("Id",""),false)) return 0;
		if(!ParseToken(Lexema("Asignment",""),false)) return 0;
		if(!ParseToken(Lexema("Agrupation","["),true)) return 0;
		if(!Listid()) return 0;
		if(!ParseToken(Lexema("Reserved","nil"),true)) return 0;
		if(!ParseToken(Lexema("Agrupation","]"),true)) return 0;
		if(!ParseToken(Lexema("Punctuation",";"),true)) return 0;
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "count"){
		// 09) Declaracion->	count id = number;
		if(!ParseToken(Lexema("Reserved","count"),true)) return 0;
		if(!ParseToken(Lexema("Id",""),false)) return 0;
		if(!ParseToken(Lexema("Asignment",""),false)) return 0;
		if(!ParseToken(Lexema("Number",""),false)) return 0;
		if(!ParseToken(Lexema("Punctuation",";"),true)) return 0;
	}else{
		std::cout << "Error sintáctico, se esperaba : while, if y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::Listid(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Number"){
		//11) Listid -> number ListidP
		if(!ParseToken(Lexema("Number",""),false)) return 0;
		if(!ListidP()) return 0;
	}else if(nextLexema._tipo == "String"){
		//10) Listid -> string ListidP
		if(!ParseToken(Lexema("String",""),false)) return 0;
		if(!ListidP()) return 0;		
	}else{
		std::cout << "Error sintáctico, se esperaba : string, number y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::ListidP(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Punctuation" && nextLexema._valor == ","){
		//12) ListidP -> , Listid
		if(!ParseToken(Lexema("Punctuation",","),true)) return 0;
		if(!Listid()) return 0;
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "nil"){
		//13) ListidP -> €
		// No hago nada
	}else{
		std::cout << "Error sintáctico, se esperaba : Punctuation, nil y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::BloqueS(){
	// 14) BloqueS -> {Sentencia}
	if(!ParseToken(Lexema("Agrupation","{"),true)) return 0;
	if(!Sentencia()) return 0;
	if(!ParseToken(Lexema("Agrupation","}"),true)) return 0;
	return 1;
}

int Anasin::BloqueE(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "else"){
		// 15) BloqueE -> else BloqueS
		if(!ParseToken(Lexema("Reserved","else"),true)) return 0;
		if(!BloqueS()) return 0;
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
		std::cout << "Error sintáctico, se esperaba : else, id, }, output, while, if, arr, count y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::Condicion(){
	// 17) Condicion -> Expresion relational Expresion
	if(!Expresion()) return 0;
	if(!ParseToken(Lexema("Relational",""),false)) return 0;
	if(!Expresion()) return 0;
	return 1;
}

int Anasin::Expresion(){
	Lexema nextLexema 		= this->_symTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_symTab->lookAheadLexema(1);
	if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 20) Expresion ->	Aarr Operador
			if(!Aarr()) return 0;
			if(!Operador()) return 0;
		}else{
			// 18) Expresion -> id Operador
			if(!ParseToken(Lexema("Id",""),false)) return 0;
			if(!Operador()) return 0;
		}
	}else if(nextLexema._tipo == "Number"){
		// 19) Expresion -> number Operador
		if(!ParseToken(Lexema("Number",""),false)) return 0;
		if(!Operador()) return 0;
	}else{
		std::cout << "Error sintáctico, se esperaba : Id, number y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::Aarr(){
	// 21) Aarr -> id AarrP
	if(!ParseToken(Lexema("Id",""),false)) return 0;
	if(!AarrP()) return 0;
	return 1;
}

int Anasin::AarrP(){
	// 22) AarrP -> [ AarrP2
	if(!ParseToken(Lexema("Agrupation","["),true)) return 0;
	if(!AarrP2()) return 0;
	return 1;
}

int Anasin::AarrP2(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Id"){
		// 23) AarrP2 -> id ]
		if(!ParseToken(Lexema("Id",""),false)) return 0;
		if(!ParseToken(Lexema("Agrupation","]"),true)) return 0;
	}else if(nextLexema._tipo == "Number"){
		// 24) AarrP2 -> number ]
		if(!ParseToken(Lexema("Number",""),false)) return 0;
		if(!ParseToken(Lexema("Agrupation","]"),true)) return 0;
	}else{
		std::cout << "Error sintáctico, se esperaba : Id, Number y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::Operacion(){
	Lexema nextLexema 		= this->_symTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_symTab->lookAheadLexema(1);
	if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 26) Operacion -> Aarr=Expresion;
			if(!Aarr()) return 0;
			if(!ParseToken(Lexema("Asignment",""),false)) return 0;
			if(!Expresion()) return 0;
			if(!ParseToken(Lexema("Punctuation",";"),true)) return 0;
		}else{
			// 25) Operacion -> id=Expresion;
			if(!ParseToken(Lexema("Id",""),false)) return 0;
			if(!ParseToken(Lexema("Asignment",""),false)) return 0;
			if(!Expresion()) return 0;
			if(!ParseToken(Lexema("Punctuation",";"),true)) return 0;
		}
	}else{
		std::cout << "Error sintáctico, se esperaba : Id y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::Operador(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Arithmetic"){
		// 27) Operador  -> arithmetic Expresion
		if(!ParseToken(Lexema("Arithmetic",""),false)) return 0;
		if(!Expresion()) return 0;
	}else if(nextLexema._tipo == "Relational" ||
			(nextLexema._tipo == "Agrupation" && nextLexema._valor == ")") ||
			(nextLexema._tipo == "Punctuation" && nextLexema._valor == ";")){
		// 28) Operador  -> €
		// No hago nada
	}else{
		std::cout << "Error sintáctico, se esperaba : Arithmetic, Relational, ) o ; y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::Impresion(){
	// 29) Impresion -> output ImpresionP
	if(!ParseToken(Lexema("Output",""),false)) return 0;
	if(!ImpresionP()) return 0;
	return 1;
}

int Anasin::ImpresionP(){
	Lexema nextLexema 		= this->_symTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_symTab->lookAheadLexema(1);
	if(nextLexema._tipo == "String"){
		// 32) ImpresionP ->	string ImpresionE
		if(!ParseToken(Lexema("String",""),false)) return 0;
		if(!ImpresionE()) return 0;
	}else if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 30) ImpresionP ->	Aarr ImpresionE
			if(!Aarr()) return 0;
			if(!ImpresionE()) return 0;
		}else{
			// 31) ImpresionP ->	id ImpresionE
			if(!ParseToken(Lexema("Id",""),false)) return 0;
			if(!ImpresionE()) return 0;
		}
	}else {
		std::cout << "Error sintáctico, se esperaba : Id, String y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}

int Anasin::ImpresionE(){
	Lexema nextLexema = this->_symTab->lookAheadLexema();
	if(nextLexema._tipo == "Punctuation" && nextLexema._valor == ";"){
		// 33) ImpresionE-> ;
		if(!ParseToken(Lexema("Punctuation",";"),true)) return 0;
	}else if(nextLexema._tipo == "Output"){
		// 34) ImpresionE-> output;
		if(!ParseToken(Lexema("Output",""),false)) return 0;
		if(!ParseToken(Lexema("Punctuation",";"),true)) return 0;
	}else{
		std::cout << "Error sintáctico, se esperaba ; output y se obtuvo: " << nextLexema._tipo << " ("<< nextLexema._valor <<")["<< this->_symTab->getOffset() <<"]" << std::endl;
		return 0;
	}
	return 1;
}





