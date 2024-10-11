# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 16:07:21 by kbassim           #+#    #+#              #
#    Updated: 2024/10/09 02:04:51 by kbassim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
CFILES = libft/libft.c\
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
		display/window.c\
		display/win_events.c\
		display/test.c\
		utils/objs.c\
		main.c\

OBJS = $(CFILES:.c=.o)
all : $(NAME)
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -lmlx -lX11 -lXext -lm
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all
.PHONE : all clean fclean re
.SECONDARY : $(OBJS)
