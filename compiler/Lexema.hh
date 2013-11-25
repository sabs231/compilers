#ifndef _LEXEMA_HH_
# define _LEXEMA_HH_
# include 	<string>

class 	Lexema{
	protected:
	public:
		Lexema();
		Lexema(std::string tipo, std::string valor);
		Lexema & operator=(Lexema const &);
		~Lexema();
		std::string _tipo;
		std::string _valor;
};

#endif
