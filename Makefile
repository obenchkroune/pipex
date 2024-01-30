CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra -Iinclude -Ilibft
CLIBS			=	-Llibft -lft
NAME			=	pipex
BONUS_NAME		=	pipex_bonus

SRC				=	./src/mandatory/cleanup.c ./src/mandatory/errors.c ./src/mandatory/ft_dprintf.c ./src/mandatory/pipex.c ./src/mandatory/parsers.c ./src/mandatory/parsers_utils.c ./src/mandatory/pipeline.c ./src/mandatory/utils.c
OBJ				=	$(SRC:.c=.o)

BONUS_SRC		=	./src/bonus/cleanup_bonus.c ./src/bonus/errors_bonus.c ./src/bonus/ft_dprintf_bonus.c ./src/bonus/get_next_line_bonus.c ./src/bonus/get_here_doc_fd.c ./src/bonus/parsers_bonus.c ./src/bonus/parsers_utils_bonus.c ./src/bonus/pipeline_bonus.c ./src/bonus/pipex_bonus.c ./src/bonus/utils_bonus.c
BONUS_OBJ		=	$(BONUS_SRC:.c=.o)

all: $(NAME)

bonus: $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C libft all
	$(CC) $(CFLAGS) $(OBJ) $(CLIBS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	make -C libft all
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
