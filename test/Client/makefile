NAME		= client

HEADER		= client.hpp

SRCS		= client.cpp

CXX			= c++

FLAGS		= 

RM			= rm -rf

OBJS		= ${SRCS:.cpp=.o}

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
			@$(CXX) $(FLAGS) $(SRCS) -o $(NAME)

%.o:%.cpp	$(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "compiling..."

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re