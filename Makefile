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
			$(SRC_DIR)input.c \
			$(SRC_DIR)threads.c \
			$(SRC_DIR)termination.c \


OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) -pthread $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

re_bonus: fclean bonus

.PHONY:	all clean fclean re
