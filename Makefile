SRC			=		src/AAutomata.cpp			\
					src/NumberAutomata.cpp		\
					src/Analex.cpp				\
					src/main.cpp

OBJS		=		$(SRC:.cpp=.o)

CXX			=		g++

NAME		=		analex

CXXFLAGS	+=		-I./include

CXXFLAGS	+=		-W -Wall -g3

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CXX) $(CXXFLAGS) -o $@ $^

clean:
					rm -f $(OBJS)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
