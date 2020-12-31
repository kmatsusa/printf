NAME=libftprintf.a

CC = gcc

CFLAG = -Wall -Wextra -Werror

SRCS = ft_printf.c ft_print_char.c ft_print_i.c ft_print_x.c ft_printf_libft.c ft_printf_libft2.c ft_read_set.c

OBJS = $(SRCS:.c=.o)

RM = rm -rf

.c.o:
	$(CC) $(CFLAG) -I ft_printf.h -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONEY: all clean fclean re
