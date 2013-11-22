SRC		=	AAutomata.cpp		\
			AgrupationAutomata.cpp	\
			Analex.cpp		\
			Anasin.cpp		\
			ArithmeticAutomata.cpp	\
			AsignmentAutomata.cpp	\
			IdAutomata.cpp		\
			Lexema.cpp		\
			NumberAutomata.cpp	\
			OutputAutomata.cpp	\
			PunctuationAutomata.cpp	\
			RelationalAutomata.cpp	\
			ReservedAutomata.cpp	\
			StringAutomata.cpp	\
			LexemeTable.cpp		\
			CuadrupleGenerator.cpp		\
			main.cpp

OBJS		=	$(SRC:.cpp=.o)

CXX			=	g++

NAME		=	analexsin

FILE_NAME	=	symbolTable.txt cuadruplesTable.txt

CXXFLAGS	+=	-I../include

CXXFLAGS	+=	-W -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) -o $@ $^

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)
		rm -f $(FILE_NAME)

re:		fclean all

.PHONY:		all clean fclean re
