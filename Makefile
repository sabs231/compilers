SRC			=		src/AAutomata.cpp			\
					src/NumberAutomata.cpp		\
					src/IdAutomata.cpp			\
					src/StringAutomata.cpp		\
					src/ArithmeticAutomata.cpp	\
					src/RelationalAutomata.cpp	\
					src/AsignmentAutomata.cpp	\
					src/PunctuationAutomata.cpp	\
					src/AgrupationAutomata.cpp	\
					src/OutputAutomata.cpp	\
					src/ReservedAutomata.cpp	\
					src/Analex.cpp				\
					src/main.cpp

OBJS		=		$(SRC:.cpp=.o)

CXX			=		g++

NAME		=		analex

CXXFLAGS	+=		-I./include

CXXFLAGS	+=		-W -Wall -Wextra -Werror -g3

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CXX) $(CXXFLAGS) -o $@ $^

clean:
					rm -f $(OBJS)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
