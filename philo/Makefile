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
				./srcs/forks.c\
				./srcs/eat.c\

CC			=	gcc

CFLAGS		=	-Werror -Wextra -Wall

LIBRARIES	=	-lpthread

LSANF		=	-g -fsanitize=address

TSANF		=	-g -fsanitize=thread

DEL			=	rm -f

OBJ			=	$(SRCS:.c=.o)

all:			$(NAME)

%.o:%.c
				$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):		$(OBJ) $(HEADER)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(LIBRARIES)

leaksan:		$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(LSANF) $(LIBRARIES)

threadsan:		$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) $(TSANF) $(LIBRARIES)

val:			$(OBJ)
				$(CC) -o $(NAME) $(SRCS) $(CFLAGS) -g $(LIBRARIES)

clean:
				$(DEL) $(OBJ)

fclean:			clean
				$(DEL) $(NAME)

re:				fclean all

.PHONY: 		all san clean fclean re
