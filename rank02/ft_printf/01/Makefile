
SRCS = ft_printf.c	\
	   options1.c	\
	   options2.c	\
	   tools.c		\

CC = clang
CFLAGS = -Wall -Wextra -Werror -c
OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:
	${RM} ${NAME}

re: fclean all
