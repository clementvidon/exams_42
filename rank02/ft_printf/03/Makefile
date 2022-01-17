.PHONY: all clean fclean re

SRCS = ft_printf.c \
	   options.c  \
	   tools.c     \

OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
CC = clang
CFLAGS = -Wall -Wextra -Werror -c
RM = rm -f

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
