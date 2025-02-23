# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 16:07:21 by kbassim           #+#    #+#              #
#    Updated: 2025/02/23 11:47:26 by kbassim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
BONUS_NAME = miniRT_bonus

CC = cc -g3
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CFILES = libft/libft.c\
		libft/ft_fullsplit.c\
		libft/ft_split.c\
		libft/ft_atodbl.c\
		libft/get_next_line/get_next_line.c\
		libft/get_next_line/get_next_line_utils.c\
		parsing/check_file.c\
		parsing/scene.c\
		parsing/scene_utils_00.c\
		parsing/scene_utils_01.c\
		parsing/read_from_file.c\
		parsing/read_from_file_01.c\
		parsing/read_from_file_02.c\
		parsing/read_from_file_03.c\
		parsing/read_from_file_04.c\
		parsing/read_from_file_05.c\
		parsing/read_from_file_06.c\
		parsing/assign_vals_01.c\
		parsing/assign_vals.c\
		parsing/assign_vals_utils.c\
		parsing/assign_vals_utils_01.c\
		parsing/assign_vals_utils_02.c\
		parsing/assign_vals_utils_03.c\
		parsing/assign_vals_utils_04.c\
		parsing/assign_vals_utils_05.c\
		display/window.c\
		display/win_events.c\
		utils/objs_00.c\
		utils/objs_01.c\
		utils/objs_02.c\
		utils/shadow.c\
		utils/world.c\
		utils/world_utils_01.c\
		utils/world_utils_02.c\
		utils/intersect_00.c\
		utils/intersect_01.c\
		utils/intersect_02.c\
		utils/intersect_03.c\
		utils/intersect_04.c\
		utils/intersect_05.c\
		utils/intersect_06.c\
		utils/reflection.c\
		utils/lighting_00.c\
		utils/lighting_01.c\
		utils/ray.c\
		utils/ray_utils.c\
		utils/ray_utils_01.c\
		utilities.c\
		utilities_01.c\
		utilities_02.c\
		utilities_03.c\
		utilities_04.c\
		utils/vectors_00.c\
		utils/vectors_01.c\
		MiniRT_bonus/sphere_bonus.c\
		utilities_bonus_00.c\
		utilities_bonus_01.c\
		utilities_bonus_02.c\
		closest_hit.c\
		
CBFILES = MiniRT_bonus/main.c\
		
MAIN = main.c\
		
OBJS = $(CFILES:.c=.o)
OBJS_B = $(CBFILES:.c=.o)
OBJ_M = $(MAIN:.c=.o)

all : $(NAME)
$(NAME) : $(OBJ_M) $(OBJS)
	$(CC) $(CFLAGS) $(CFILES) $(MAIN) -o $(NAME) -lmlx -lX11 -lXext -lm

bonus : $(BONUS_NAME)
$(BONUS_NAME) : $(OBJS) $(OBJS_B)
	$(CC) $(CFLAGS) $(CBFILES) $(CFILES) -o $(BONUS_NAME) -lmlx -lX11 -lXext -lm

clean :
	rm -rf $(OBJS) $(OBJS_B) $(OBJ_M)
fclean : clean
	rm -rf $(NAME) $(BONUS_NAME)
re : fclean all
.PHONE : all clean fclean re
.SECONDARY : $(OBJS)
