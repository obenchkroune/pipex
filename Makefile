CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -Iinclude
NAME		=	pipex
BONUS_NAME	=	pipex_bonus

SRC_FILES	=	cleanup.c errors.c main.c parsers.c utils.c
BONUS_FILES	=	cleanup_bonus.c errors_bonus.c main_bonus.c parsers_bonus.c utils_bonus.c

SRC			=	$(addprefix ./source/mandatory/, $(SRC_FILES))
OBJ			=	$(SRC:.c=.o)

BONUS_SRC	=	$(addprefix ./source/bonus/, $(BONUS_FILES))
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

LIBFT		=	libft/libft.a
LIBS		=	-L./libft -lft

all: $(NAME)

bonus: $(BONUS_NAME)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	make -C libft all

$(NAME): $(OBJ) $(LIBFT) ./include/pipex.h
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)

clean:
	make -C libft clean
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME) $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ) ./include/pipex_bonus.h
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $@ $(LIBS)

re: fclean all

.PHONY: all clean fclean bonus re 
