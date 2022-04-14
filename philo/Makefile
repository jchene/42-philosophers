NAME		=	philo

HEADER		=	./philo.h

SRCS		=	./srcs/main.c\
				./srcs/lib.c\
				./srcs/input.c\
				./srcs/memory.c\
				./srcs/init.c\
				./srcs/philos.c\
				./srcs/mutex.c\
				./srcs/time.c\
				./srcs/print.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall

PHILO_FLAGS	=	-lpthread

SANFLAGS	=	-g -fsanitize=address

DEL			=	rm -f

OBJ			=	$(SRCS:.c=.o)

all:			$(NAME)

%.o:%.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(PHILO_FLAGS)

san:			$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(SANFLAGS) $(PHILO_FLAGS)

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all san clean fclean re
