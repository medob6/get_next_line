SRC = get_next_line.c get_next_line_utils.c
SRCB = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ = $(SRC:%.c=%.o)
OBJ_BONUS = $(SRCB:%.c=%.o)

NAME = libgetnextline.a

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ_BONUS)

%.o: %.c
	cc -I. $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all