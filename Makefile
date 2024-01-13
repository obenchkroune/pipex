CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinclude -Ilibft -fsanitize=address -g
NAME		=	pipex

SRC			=	./source/errors.c ./source/ft_dprintf.c ./source/main.c ./source/parsers.c ./source/parsers_utils.c ./source/pipeline.c ./source/utils.c
OBJ			=	$(SRC:.c=.o)

BONUS_SRC	=	$(shell find ./source/bonus -type f -name *.c)
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

LIBFT		=	libft/libft.a
LIBS		=	-Llibft -lft

all: $(NAME)

$(LIBFT):
	make -C libft all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) ./include/pipex.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

bonus: $(BONUS_OBJ) $(LIBFT) ./include/pipex_bonus.h
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBS) -o $(NAME)

clean:
	make -C libft clean
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus $(NAME)