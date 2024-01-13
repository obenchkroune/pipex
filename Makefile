CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinclude -Ilibft
NAME		=	pipex

SRC			=	./source/errors.c ./source/ft_dprintf.c ./source/main.c ./source/parsers.c ./source/parsers_utils.c ./source/pipeline.c ./source/utils.c
OBJ			=	$(SRC:.c=.o)

LIBS		=	-Llibft -lft

LIBFT		=	libft/libft.a

all: $(NAME)

$(LIBFT):
	make -C libft all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re