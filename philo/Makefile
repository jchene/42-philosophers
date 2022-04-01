NAME		=	philo

HEADER		=	./philo.h

SRCS		=	./srcs/main.c\
				./srcs/lib.c\
				./srcs/input.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall -g

PHILO_FLAGS	=	-lpthread -D_REENTRANT

SANFLAGS	=	-fsanitize=address

DEL			=	rm -f

OBJ			=	$(SRCS:.c=.o)

all:			$(NAME)

%.o:%.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(PHILO_FLAGS)

san:			$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(PHILO_FLAGS) $(SANFLAGS)

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all san clean fclean re