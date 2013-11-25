#include 	<fstream>
#include 	<iostream>
#include 	<iomanip>
#include 	"LexemeTable.hh"

LexemeTable::LexemeTable(){
	this->_indexOffset = 0;
}

LexemeTable::LexemeTable(LexemeTable const &other){
	this->_indexOffset = 0;
	this->_symTable = other._symTable;
}

LexemeTable & LexemeTable::operator=(LexemeTable const &other){
	if (this != &other)
		this->_symTable = other._symTable;
	return (*this);
}

LexemeTable::~LexemeTable(){
}

void LexemeTable::insert(Lexema newLexema){
	this->_symTable.push_back(newLexema);
}

void LexemeTable::writeToFile(){
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

Lexema LexemeTable::getLexema(){
	if(this->_indexOffset >= this->_symTable.size()){
		return Lexema("$","");
	}
	return this->_symTable.at(this->_indexOffset++);
}

Lexema LexemeTable::lookAheadLexema(int lookahead){
	if(this->_indexOffset >= this->_symTable.size()){
		return Lexema("$","");
	}
	return this->_symTable.at(this->_indexOffset + lookahead);
}

int LexemeTable::getSize(){
	return this->_symTable.size();
}

int LexemeTable::getOffset(){
	return this->_indexOffset;
}

void LexemeTable::resetOffset(){
	this->_indexOffset = 0;
}