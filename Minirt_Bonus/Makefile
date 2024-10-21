NAME = miniRT
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -fsanitize=address -g

SRCS = src/intersect.c \
       src/lighting.c \
       src/ray.c \
       src/vectors.c \
	   libft/libft.c\
	   libft/ft_fullsplit.c\
	   libft/ft_split.c\
	   libft/ft_atodbl.c\
	   libft/get_next_line/get_next_line.c\
	   libft/get_next_line/get_next_line_utils.c\
	   parsing/check_file.c\
	   parsing/scene.c\
	   parsing/read_from_file.c\
	   parsing/assign_vals.c\
	   parsing/assign_vals_utils.c\
	   objs.c\
       src/main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  -lmlx -lX11 -lXext -lm

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re