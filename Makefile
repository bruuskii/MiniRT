NAME = miniRT
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror
CFILES = libft/libft.c\
		libft/libft00.c\
		libft/get_next_line/get_next_line.c\
		libft/get_next_line/get_next_line_utils.c\
		parsing/check_file.c\
		parsing/read_from_file.c\
		display/window.c\
		display/win_events.c\
		display/test.c\
		main.c\

OBJS = $(CFILES:.c=.o)
all : $(NAME)
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -Lmlx_directory -lmlx -lX11 -lXext -lm
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all
.PHONE : all clean fclean re
.SECONDARY : $(OBJS)
