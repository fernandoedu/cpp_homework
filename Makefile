NAME		=	test_deck
SRCS		=  	test.cpp
OBJS		= 	$(SRCS:.cpp=.o)
CC			= 	c++
FLAGS		=	-std=c++17 -g
WARN		=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(SRCS)
			@ $(CC) $(FLAGS) $(WARN) $(SRCS) -o $(NAME)

clean:		
			@ rm -f $(OBJS)

fclean:		clean
			@ rm -f $(NAME)

.PHONY: 	all fclean clean
