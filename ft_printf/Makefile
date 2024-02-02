NAME = libftprintf.a

.DEFAULT_GOAL := all

SRCS =			ft_printf.c \
				ft_putptr.c \
				ft_unsigned_putnbr_len.c \
				ft_putnbr_hex_len.c \
				ft_putnbr_hex_upper_len.c \
				ft_putchar_len_fd.c \
				ft_putnbr_len.c \
				ft_putstr_len.c


OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
