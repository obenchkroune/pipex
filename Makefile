NAME		=	pipex
BONUS_NAME	=	pipex_bonus

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinclude -Ilibft
CLIBS		=	-Llibft -lft

SRC			=	./source/errors.c ./source/ft_dprintf.c ./source/get_av.c ./source/main.c ./source/parsers.c ./source/parsers_utils.c ./source/pipeline.c ./source/utils.c
OBJ			=	$(SRC:.c=.o)

BONUS_SRC	=	./source/bonus/errors_bonus.c ./source/bonus/ft_dprintf_bonus.c ./source/bonus/get_av_bonus.c ./source/bonus/get_next_line_bonus.c ./source/bonus/main_bonus.c ./source/bonus/parsers_bonus.c ./source/bonus/parsers_utils_bonus.c ./source/bonus/pipeline_bonus.c ./source/bonus/utils_bonus.c ./source/bonus/handle_here_doc_bonus.c
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

LIBFT		=	libft/libft.a


all: $(NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	make -C libft all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(CLIBS) -o $@

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(CLIBS) -o $(BONUS_NAME)

clean:
	make -C libft clean
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
.SECONDARY: $(OBJ) $(BONUS_OBJ)
