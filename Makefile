SRC			=		src/AAutomata.cpp			\
					src/NumberAutomata.cpp

OBJS		=		$(SRC:.cpp=.o)

CXX			=		g++

NAME		=		analex

CXXFLAGS	+=		-I./include

CXXFLAGS	+=		-W -Wall

all:				$(NAME)

$(NAME):			$(OBJS)
					$(CXX) $(CXXFLAGS) -o $@ $^

clean:
					rm -f $(OBJS)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re
