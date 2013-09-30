SRC			=		src/AAutomata.cpp			\
					src/NumberAutomata.cpp		\
					src/IdAutomata.cpp			\
					src/StringAutomata.cpp		\
					src/ArithmeticAutomata.cpp	\
					src/RelationalAutomata.cpp	\
					src/AsignmentAutomata.cpp	\
					src/PunctuationAutomata.cpp	\
					src/AgrupationAutomata.cpp	\
					src/OutputAutomata.cpp		\
					src/ReservedAutomata.cpp	\
					src/SymbolTable.cpp			\
					src/Analex.cpp				\
					src/main.cpp

OBJS		=		$(SRC:.cpp=.o)

CXX			=		g++

NAME		=		analex

FILE_NAME	=		symbolTable.txt

CXXFLAGS	+=		-I./include

CXXFLAGS	+=		-W -Wall -Wextra -Werror

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CXX) $(CXXFLAGS) -o $@ $^

clean:
					rm -f $(OBJS)

fclean:				clean
					rm -f $(NAME)
					rm -f $(FILE_NAME)

re:					fclean all

.PHONY:				all clean fclean re
