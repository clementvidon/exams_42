NAME		= out

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -Wconversion
CFLAGS		:= $(CFLAGS)
SRCS		= main.c \
			  ../try.c
OBJS		:= $(SRCS:%.c=%.o)

RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
