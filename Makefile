CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinclude -Ilibft
NAME		=	pipex
BONUS_NAME	=	.pipex_bonus

SRC			=	./source/errors.c ./source/ft_dprintf.c ./source/main.c ./source/parsers.c ./source/parsers_utils.c ./source/pipeline.c ./source/utils.c
OBJ			=	$(SRC:.c=.o)

BONUS_SRC	=	./source/bonus/errors_bonus.c ./source/bonus/ft_dprintf_bonus.c ./source/bonus/get_next_line_bonus.c ./source/bonus/main_bonus.c ./source/bonus/parsers_bonus.c ./source/bonus/parsers_utils_bonus.c ./source/bonus/pipeline_bonus.c ./source/bonus/utils_bonus.c
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
