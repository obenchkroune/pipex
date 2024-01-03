CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinclude
NAME		=	pipex

SRC			=	source/cleanup.c source/errors.c source/main.c source/parsers.c source/utils.c
OBJ			=	$(patsubst source/%.c, objects/%.o, $(SRC))

LIBFT		=	libft/libft.a

all: $(NAME)

objects/%.o: source/%.c
	@mkdir -p objects
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	make -C libft all

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBFT)

clean:
	make -C libft clean
	rm -rf objects

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re