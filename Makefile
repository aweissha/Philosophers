NAME = philo

LIBFT = libft/libft.a
SRC_DIR = src/

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f


SRCS = 		$(SRC_DIR)philo.c \
			$(SRC_DIR)utils.c \
			$(SRC_DIR)error.c \
			$(SRC_DIR)init.c \
			$(SRC_DIR)eat_utils.c \
			$(SRC_DIR)action.c \


OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY:	all clean fclean re
