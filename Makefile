CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinclude -Ilibft -fsanitize=address -g
NAME		=	pipex
BONUS_NAME	=	.pipex_bonus

SRC			=	$(wildcard ./source/*.c)
OBJ			=	$(SRC:.c=.o)

BONUS_SRC	=	$(wildcard ./source/bonus/*.c)
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

LIBFT		=	libft/libft.a
LIBS		=	-Llibft -lft


all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	make -C libft all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ)
	@touch $(BONUS_NAME)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBS) -o $(NAME)

clean:
	make -C libft clean
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
