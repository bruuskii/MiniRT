NAME = miniRT
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror
CFILES = display/window.c\
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
