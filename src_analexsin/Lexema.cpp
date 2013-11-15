#include 	<fstream>
#include 	<iostream>
#include 	<iomanip>
#include 	"Lexema.hh"

Lexema::Lexema(){
	this->_tipo = "";
	this->_valor= "";
}

Lexema::Lexema(std::string tipo, std::string valor){
	this->_tipo  = tipo;
	this->_valor = valor;
}

Lexema & Lexema::operator=(Lexema const &other){
	if (this != &other){
		this->_tipo  = other._tipo;
		this->_valor = other._valor;
	}
	return (*this);
}

Lexema::~Lexema(){
}
