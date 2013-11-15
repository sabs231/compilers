#include 	<fstream>
#include 	<iostream>
#include 	<iomanip>
#include 	"SymbolTable.hh"

SymbolTable::SymbolTable(){
	this->_indexOffset = 0;
}

SymbolTable::SymbolTable(SymbolTable const &other){
	this->_indexOffset = 0;
	this->_symTable = other._symTable;
}

SymbolTable & SymbolTable::operator=(SymbolTable const &other){
	if (this != &other)
		this->_symTable = other._symTable;
	return (*this);
}

SymbolTable::~SymbolTable(){
}

void SymbolTable::insert(Lexema newLexema){
	this->_symTable.push_back(newLexema);
}

void SymbolTable::writeToFile(){
	std::vector<Lexema>::iterator it;
	std::ofstream	outputFile;
	outputFile.open("symbolTable.txt", std::ios::out);
	if (outputFile.is_open()){
		outputFile << "Type" << std::setw(25) << "Lexeme" << std::endl;
		for (it = this->_symTable.begin(); it != this->_symTable.end(); ++it)
			outputFile << it->_tipo << " ==> " << it->_valor << std::endl;
		outputFile.close();
	}else
		std::cerr << "Unable to create symbolTable.txt" << std::endl;
}

Lexema SymbolTable::getLexema(){
	if(this->_indexOffset >= this->_symTable.size()){
		return Lexema("$","");
	}
	return this->_symTable.at(this->_indexOffset++);
}

Lexema SymbolTable::lookAheadLexema(int lookahead){
	if(this->_indexOffset >= this->_symTable.size()){
		return Lexema("$","");
	}
	return this->_symTable.at(this->_indexOffset + lookahead);
}

int SymbolTable::getSize(){
	return this->_symTable.size();
}

int SymbolTable::getOffset(){
	return this->_indexOffset;
}