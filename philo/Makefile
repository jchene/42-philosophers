NAME		=	philo

HEADER		=	./philo.h

SRCS		=	./srcs/*.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall -g

SANFLAGS	=	-fsanitize=address

DEL			=	rm -f

OBJ			=	$(SRCS:.c=.o)

all:			$(NAME)

%.o:%.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS)

san:			$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(SANFLAGS)

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all san clean fclean re