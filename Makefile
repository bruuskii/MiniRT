# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 16:07:21 by kbassim           #+#    #+#              #
#    Updated: 2024/12/02 16:50:40 by kbassim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
BONUS_NAME = miniRT_bonus

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
		utils/objs.c\
		utils/shadow.c\
		utils/intersect.c\
		utils/reflection.c\
		utils/lighting.c\
		utils/ray.c\
		utils/vectors.c\

MAIN = main.c\
		
OBJS = $(CFILES:.c=.o)
OBJS_B = $(CBFILES:.c=.o)
OBJ_M = $(MAIN:.c=.o)

all : $(NAME)
$(NAME) : $(OBJS) $(OBJ_M)
	$(CC) $(CFLAGS) $(CFILES) $(MAIN) -o $(NAME) -lmlx -lX11 -lXext -lm

bonus : $(BONUS_NAME)
$(BONUS_NAME) : $(OBJS) $(OBJS_B)
	$(CC) $(CFLAGS) $(CFILES) $(CBFILES) -o $(BONUS_NAME) -lmlx -lX11 -lXext -lm

clean :
	rm -rf $(OBJS) $(OBJS_B) $(OBJ_M)
fclean : clean
	rm -rf $(NAME) $(BONUS_NAME)
re : fclean all
.PHONE : all clean fclean re
.SECONDARY : $(OBJS)
