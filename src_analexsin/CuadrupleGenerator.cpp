#include 	<fstream>
#include 	<iostream>
#include 	"CuadrupleGenerator.hh"
#define		DEBUG	0

CuadrupleGenerator::CuadrupleGenerator(LexemeTable *symTab): _lexTab(symTab){
	Tcount = 0;
}

CuadrupleGenerator::CuadrupleGenerator(CuadrupleGenerator const &other){
	this->_lexTab = other._lexTab;
	Tcount = 0;
}

CuadrupleGenerator & CuadrupleGenerator::operator=(CuadrupleGenerator const &other){
	if (this != &other){
		this->_lexTab = other._lexTab;
		Tcount = other.Tcount;
	}
	return (*this);
}

CuadrupleGenerator::~CuadrupleGenerator(){
}

int CuadrupleGenerator::run(LexemeTable *lexTab){
	this->_lexTab = lexTab;
	Tcount	= 0;
	if(this->_lexTab == NULL){
		return(Cuadruples.size());
	}
	std::cout << std::endl << "-- Iniciando Generador de Cuádruplos --" << std::endl << std::endl;
	this->_lexTab->resetOffset();
	this->Cuadruples = Sentencia(0);
	return Cuadruples.size();
}

std::list<std::string> CuadrupleGenerator::Sentencia(unsigned int currentCount){
	std::list<std::string> newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && (nextLexema._valor == "while" || nextLexema._valor == "if")){
		// 01) Sentencia ->	EControl Sentencia
		std::list<std::string> EControlList = EControl(currentCount);
		newCuadruples.splice (newCuadruples.end(), EControlList);
		std::list<std::string> SentenciaList = Sentencia(currentCount + newCuadruples.size());
		newCuadruples.splice (newCuadruples.end(), SentenciaList);
	}else if(nextLexema._tipo == "Id"){
		// 02) Sentencia ->	Operacion Sentencia 
		std::list<std::string> OperacionList = Operacion();
		newCuadruples.splice (newCuadruples.end(), OperacionList);		
		std::list<std::string> SentenciaList = Sentencia(currentCount + newCuadruples.size());
		newCuadruples.splice (newCuadruples.end(), SentenciaList);
	}else if(nextLexema._tipo == "Reserved" && (nextLexema._valor == "arr" || nextLexema._valor == "count")){
		// 03) Sentencia ->	Declaracion Sentencia
		std::list<std::string> DeclaracionList = Declaracion();
		newCuadruples.splice (newCuadruples.end(), DeclaracionList);
		std::list<std::string> SentenciaList = Sentencia(currentCount + newCuadruples.size());
		newCuadruples.splice (newCuadruples.end(), SentenciaList);
	}else if(nextLexema._tipo == "Output"){
		// 04) Sentencia ->	Impresión Sentencia
		std::list<std::string> ImpresionList = Impresion();
		newCuadruples.splice (newCuadruples.end(), ImpresionList);
		std::list<std::string> SentenciaList = Sentencia(currentCount + newCuadruples.size());
		newCuadruples.splice (newCuadruples.end(), SentenciaList);
	}else if(nextLexema._tipo == "Agrupation" && nextLexema._valor == "}"){
		// 02) Sentencia -> €
	}else if(nextLexema._tipo == "$"){
		// Ya terminé :)
		std::ostringstream cuadruploStream;
		cuadruploStream << "(END, _, _, _)";
		newCuadruples.push_back(cuadruploStream.str());
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::EControl(unsigned int currentCount){
	std::list<std::string> newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "while"){
		// 06) EControl    ->	while(Condicion)BloqueS
		// (<, contador, 5, T2) <- Condicion empieza en currentCount
		// (IFN, T2, goto28, _) <- Salto fuera del ciclo sin no se cumple (newCuadruples)
		// BloqueS
		// (GOTO, goto9, _, _) <- Salto a la linea original nuevamente
		this->_lexTab->getLexema();
		this->_lexTab->getLexema();
		ReturnCuadrupleInfo rciCondicion = Condicion();
		this->_lexTab->getLexema();
		std::list<std::string> BloqueSList = BloqueS(rciCondicion.Clist.size() + currentCount + 1); // Mas uno del IF
		
		std::ostringstream ifnStream;
		ifnStream << "(IFN, T" << rciCondicion.Tname << ", goto"<< (rciCondicion.Clist.size() + BloqueSList.size() + currentCount + 2) << ", _)"; // Mas dos del If y del GOTO

		newCuadruples.splice(newCuadruples.end(), rciCondicion.Clist);
		newCuadruples.push_back(ifnStream.str());
		newCuadruples.splice(newCuadruples.end(), BloqueSList);
		
		std::ostringstream gotoStream;
		gotoStream << "(GOTO, goto"<< currentCount << ", _, _)";
		newCuadruples.push_back(gotoStream.str());
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "if"){
		// 07) EControl    ->	if(Condicion)BloqueS BloqueE
		// (CONDICION,_,_,_)
		// (IFN, TCondicion, gotoElse,_)
		// Codigo IF
		// (GOTO, gotoEndOfIf, _, _)
		// Codigo Else
		this->_lexTab->getLexema();
		this->_lexTab->getLexema();
		ReturnCuadrupleInfo rciCondicion = Condicion();
		this->_lexTab->getLexema();
		std::list<std::string> BloqueSList = BloqueS(rciCondicion.Clist.size() + currentCount + 1); // Mas uno del IF
		std::list<std::string> BloqueEList = BloqueE(rciCondicion.Clist.size() + currentCount + BloqueSList.size() + 1); // M
		
		std::ostringstream ifnStream;
		ifnStream << "(IFN, T" << rciCondicion.Tname << ", goto"<< (rciCondicion.Clist.size() + BloqueSList.size() + currentCount + 2) << ", _)";
		std::ostringstream gotoStream;
		gotoStream << "(GOTO, goto"<< (rciCondicion.Clist.size() + BloqueSList.size() + BloqueEList.size() + currentCount + 2) << ", _, _)";
		
		newCuadruples.splice(newCuadruples.end(), rciCondicion.Clist);
		newCuadruples.push_back(ifnStream.str());
		newCuadruples.splice(newCuadruples.end(), BloqueSList);
		newCuadruples.push_back(gotoStream.str());
		newCuadruples.splice(newCuadruples.end(), BloqueEList);
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::Declaracion(){
	std::list<std::string> newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "arr"){
		// 08) Declaracion->	arr id = [Listid nil];
		Lexema larr			= this->_lexTab->getLexema();
		Lexema lid 			= this->_lexTab->getLexema();
		Lexema lasignment	= this->_lexTab->getLexema();
		Lexema lAgrupationO	= this->_lexTab->getLexema();
		std::list<std::string> ListidList = Listid(0, lid._valor);
		newCuadruples.splice (newCuadruples.end(), ListidList);
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
		std::ostringstream cuadruploStream;
		cuadruploStream << "(=," << lid._valor << "," << lnumber._valor << ", _)";
		newCuadruples.push_back(cuadruploStream.str());
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::Listid(int index, std::string idName){
	std::list<std::string> newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Number"){
		//11) Listid -> number ListidP
		// (=, a[0], 1, T1)
		Lexema lnumber	= this->_lexTab->getLexema();
		std::ostringstream cuadruploNumberStream;
		cuadruploNumberStream << "(=," << idName << "[" << index << "]," << lnumber._valor << ", _)";
		newCuadruples.push_back(cuadruploNumberStream.str());
		std::list<std::string> ListidPList = ListidP(index+1, idName);
		newCuadruples.splice (newCuadruples.end(), ListidPList);
	}else if(nextLexema._tipo == "String"){
		//10) Listid -> string ListidP
		// (=, a[0], "string", T1)
		Lexema lString	= this->_lexTab->getLexema();
		std::ostringstream cuadruploStringStream;
		cuadruploStringStream << "(=," << idName << "[" << index << "]," << lString._valor << ", _)";
		newCuadruples.push_back(cuadruploStringStream.str());
		std::list<std::string> ListidPList = ListidP(index+1, idName);
		newCuadruples.splice (newCuadruples.end(), ListidPList);	
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::ListidP(int index, std::string idName){
	std::list<std::string> newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Punctuation" && nextLexema._valor == ","){
		//12) ListidP -> , Listid
		this->_lexTab->getLexema();
		std::list<std::string> ListidList = Listid(index, idName);
		newCuadruples.splice (newCuadruples.end(), ListidList);
	}else if(nextLexema._tipo == "Reserved" && nextLexema._valor == "nil"){
		//13) ListidP -> €
		// No hago nada
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::BloqueS(unsigned int currentCount){
	std::list<std::string> newCuadruples;
	// 14) BloqueS -> {Sentencia}
	this->_lexTab->getLexema();
	newCuadruples = Sentencia(currentCount);
	this->_lexTab->getLexema();
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::BloqueE(unsigned int currentCount){
	std::list<std::string> newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Reserved" && nextLexema._valor == "else"){
		// 15) BloqueE -> else BloqueS
		this->_lexTab->getLexema();
		std::list<std::string> BloqueSList = BloqueS(currentCount);
		newCuadruples.splice (newCuadruples.end(), BloqueSList);
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
	}
	return newCuadruples;
}

ReturnCuadrupleInfo CuadrupleGenerator::Condicion(){
	ReturnCuadrupleInfo newCuadruples;
	/* XXX Come 3 lexemas para este ejemplo
	this->_lexTab->getLexema();
	this->_lexTab->getLexema();
	this->_lexTab->getLexema();
	newCuadruples.Tname = 0;
	newCuadruples.Clist.push_back(std::string("(CONDICION,_,_,T0)"));
	*/
	// 17) Condicion -> Expresion relational Expresion
	ReturnCuadrupleInfo rcil = Expresion();
	Lexema lRelacional		 = this->_lexTab->getLexema();
	ReturnCuadrupleInfo rcir = Expresion();
	std::ostringstream condicionStream;
	condicionStream << "("<< lRelacional._valor <<", T" << rcil.Tname << ",T"<< rcir.Tname <<", T" << Tcount << ")";
	newCuadruples.Tname = Tcount++;
	newCuadruples.Clist.splice (newCuadruples.Clist.end(), rcil.Clist);
	newCuadruples.Clist.splice (newCuadruples.Clist.end(), rcir.Clist);
	newCuadruples.Clist.push_back(condicionStream.str());
	return newCuadruples;
}

ReturnCuadrupleInfo CuadrupleGenerator::Expresion(){
	ReturnCuadrupleInfo newCuadruples;
	Lexema nextLexema 		= this->_lexTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_lexTab->lookAheadLexema(1);
	if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 20) Expresion ->	Aarr Operador
			Lexema lid		= this->_lexTab->getLexema();
			this->_lexTab->getLexema();
			Lexema larridx	= this->_lexTab->getLexema();
			this->_lexTab->getLexema();
			std::ostringstream arrStream;
			arrStream << lid._valor << "[" << larridx._valor << "]";
			newCuadruples = Operador(arrStream.str());
		}else{
			// 18) Expresion -> id Operador
			Lexema lid		= this->_lexTab->getLexema();
			newCuadruples = Operador(lid._valor);
		}
	}else if(nextLexema._tipo == "Number"){
		// 19) Expresion -> number Operador
		Lexema lid		= this->_lexTab->getLexema();
		newCuadruples = Operador(lid._valor);
	}
	return newCuadruples;
}

ReturnCuadrupleInfo CuadrupleGenerator::Operador(std::string leftOperator){
	ReturnCuadrupleInfo newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Arithmetic"){
		// 27) Operador  -> arithmetic Expresion
		Lexema aritmetico = this->_lexTab->getLexema();
		ReturnCuadrupleInfo rciExpresion = Expresion();
		std::ostringstream OperatorStream;
		OperatorStream << "("<< aritmetico._valor <<"," << leftOperator << ",T"<< rciExpresion.Tname <<", T" << Tcount << ")";
		rciExpresion.Clist.push_back(OperatorStream.str());
		newCuadruples.Tname = Tcount++;
		newCuadruples.Clist.splice (newCuadruples.Clist.end(), rciExpresion.Clist);
	}else if(nextLexema._tipo == "Relational" ||
			(nextLexema._tipo == "Agrupation" && nextLexema._valor == ")") ||
			(nextLexema._tipo == "Punctuation" && nextLexema._valor == ";")){
		// 28) Operador  -> €
		// No hago nada
		std::ostringstream OperatorStream;
		OperatorStream << "(+," << leftOperator << ", 0, T" << Tcount << ")";
		newCuadruples.Tname = Tcount++;
		newCuadruples.Clist.push_back(OperatorStream.str());
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::Operacion(){
	std::list<std::string> newCuadruples;
	Lexema nextLexema 		= this->_lexTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_lexTab->lookAheadLexema(1);
	if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 26) Operacion -> Aarr=Expresion;
			Lexema lid		= this->_lexTab->getLexema();
			this->_lexTab->getLexema();
			Lexema arrCont	= this->_lexTab->getLexema();
			this->_lexTab->getLexema();
			this->_lexTab->getLexema();
			ReturnCuadrupleInfo rciExpresion = Expresion();
			this->_lexTab->getLexema();
			newCuadruples.splice (newCuadruples.end(), rciExpresion.Clist);
			std::ostringstream cuadruploExpresionStream;
			cuadruploExpresionStream << "(=," << lid._valor << "["<< arrCont._valor <<"], T" << rciExpresion.Tname << ", _)";
			newCuadruples.push_back(cuadruploExpresionStream.str());
		}else{
			// 25) Operacion -> id=Expresion;
			Lexema lid = this->_lexTab->getLexema();
			this->_lexTab->getLexema();
			ReturnCuadrupleInfo rciExpresion = Expresion();
			this->_lexTab->getLexema();
			newCuadruples.splice (newCuadruples.end(), rciExpresion.Clist);
			std::ostringstream cuadruploExpresionStream;
			cuadruploExpresionStream << "(=," << lid._valor << ", T" << rciExpresion.Tname << ", _)";
			newCuadruples.push_back(cuadruploExpresionStream.str());
		}
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::Impresion(){
	std::list<std::string> newCuadruples;
	// 29) Impresion -> output ImpresionP
	this->_lexTab->getLexema();
	std::list<std::string> ImpresionPList = ImpresionP();
	newCuadruples.splice (newCuadruples.end(), ImpresionPList);
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::ImpresionP(){
	std::list<std::string> newCuadruples;
	Lexema nextLexema 		= this->_lexTab->lookAheadLexema();
	Lexema nextnextLexema	= this->_lexTab->lookAheadLexema(1);
	if(nextLexema._tipo == "String"){
		// 32) ImpresionP ->	string ImpresionE
		// (PRINT, "String", _, _)
		Lexema lString = this->_lexTab->getLexema();
		std::ostringstream cuadruploPrintStream;
		cuadruploPrintStream << "(PRINT," << lString._valor << ", _, _)";
		newCuadruples.push_back(cuadruploPrintStream.str());
		std::list<std::string> ImpresionEList = ImpresionE();
		newCuadruples.splice (newCuadruples.end(), ImpresionEList);
	}else if(nextLexema._tipo == "Id"){
		if(nextnextLexema._tipo == "Agrupation" && nextnextLexema._valor == "["){
			// 30) ImpresionP ->	Aarr ImpresionE
			// Nos saltamos Aarr() y obtenemos los 2 cuadruplos que necesitamos
			Lexema lId = this->_lexTab->getLexema();
			Lexema lAgrup01 = this->_lexTab->getLexema();
			Lexema lIdOrNumber = this->_lexTab->getLexema();
			Lexema lAgrup02 = this->_lexTab->getLexema();
			std::ostringstream cuadruploArrVarPrintStream;
			std::ostringstream cuadruploArrPrintStream;
			cuadruploArrVarPrintStream << "([]," << lId._valor << "," << lIdOrNumber._valor << ", T"<< Tcount <<")";
			cuadruploArrPrintStream << "(PRINT, T" << Tcount << ", _, _)";
			newCuadruples.push_back(cuadruploArrVarPrintStream.str());
			newCuadruples.push_back(cuadruploArrPrintStream.str());
			Tcount++;
			std::list<std::string> ImpresionEList = ImpresionE();
			newCuadruples.splice (newCuadruples.end(), ImpresionEList);
		}else{
			// 31) ImpresionP ->	id ImpresionE
			// (PRINT, id, _, _)
			Lexema lId = this->_lexTab->getLexema();
			std::ostringstream cuadruploPrintStream;
			cuadruploPrintStream << "(PRINT," << lId._valor << ", _, _)";
			newCuadruples.push_back(cuadruploPrintStream.str());
			std::list<std::string> ImpresionEList = ImpresionE();
			newCuadruples.splice (newCuadruples.end(), ImpresionEList);
		}
	}
	return newCuadruples;
}

std::list<std::string> CuadrupleGenerator::ImpresionE(){
	std::list<std::string> newCuadruples;
	Lexema nextLexema = this->_lexTab->lookAheadLexema();
	if(nextLexema._tipo == "Punctuation" && nextLexema._valor == ";"){
		// 33) ImpresionE-> ;
		this->_lexTab->getLexema();
	}else if(nextLexema._tipo == "Output"){
		// 34) ImpresionE-> output;
		this->_lexTab->getLexema();
		this->_lexTab->getLexema();
		std::ostringstream cuadruploPrintLnStream;
		cuadruploPrintLnStream << "(PRINT,\"\\n\", _, _)";
		newCuadruples.push_back(cuadruploPrintLnStream.str());
	}
	return newCuadruples;
}

void CuadrupleGenerator::writeToFile(){
	std::ofstream	outputFile;
	outputFile.open("cuadruplesTable.txt", std::ios::out);
	if (outputFile.is_open()){
		for (std::list<std::string>::iterator it=this->Cuadruples.begin(); it != this->Cuadruples.end(); ++it){
			outputFile <<*it << std::endl;
		}
		outputFile.close();
	}else
		std::cerr << "Unable to create cuadruplesTable.txt" << std::endl;
}
void CuadrupleGenerator::printCuadruples(){
	unsigned int i = 0;
	for (std::list<std::string>::iterator it=this->Cuadruples.begin(); it != this->Cuadruples.end(); ++it){
		std::cout << "[" << i++ << "]" <<*it << std::endl;
	}
	std::cout << std::endl << "Cuádruplos generados: " << this->Cuadruples.size() << std::endl;
}



