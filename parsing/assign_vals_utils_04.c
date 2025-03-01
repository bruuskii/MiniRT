/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils_04.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:32:58 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/24 12:48:23 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_cam_utils(t_cam **cam, char **lst, int i)
{
	if (i == 1)
		ft_assign_cam_utils_pos(cam, lst[i]);
	else if (i == 2)
		ft_assign_cam_utils_dir(cam, lst[i]);
	else if (i == 3)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Field of view has non numerical", 1);
		(*cam)->fov = ft_atodbl(lst[i]);
		if ((*cam)->fov > 360)
			ft_print_and_exit("Field of view overflow", 1);
	}
}

void	ft_assign_light_dir(t_light **lt, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("Light direction has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("Light direction incorrect", 1);
	(*lt)->dir = malloc(sizeof(t_vctr));
	(*lt)->dir->x = ft_atodbl(tmp[0]);
	(*lt)->dir->y = ft_atodbl(tmp[1]);
	(*lt)->dir->z = ft_atodbl(tmp[2]);
	ft_lstfree(tmp);
}

void	ft_assign_light_color(t_light **lt, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("Light color has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("Light color incorrect", 1);
	(*lt)->color = malloc(sizeof(t_vctr));
	(*lt)->color->x = ft_atodbl(tmp[0]);
	(*lt)->color->y = ft_atodbl(tmp[1]);
	(*lt)->color->z = ft_atodbl(tmp[2]);
	if (((*lt)->color->x > 255 || (*lt)->color->y > 255
			|| (*lt)->color->z > 255) || ((*lt)->color->x < 0
			|| (*lt)->color->y < 0 || (*lt)->color->z < 0))
		ft_print_and_exit("Light has wrong color parameters", 1);
	ft_lstfree(tmp);
}

void	ft_assign_light_utils(t_light **lt, char **lst, int i, int fl)
{
	int	c;

	c = ft_lst_count(lst);
	if (i == 0)
		ft_assign_light_dir(lt, lst[i]);
	else if (i == 1)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Light brightness has non numerical", 1);
		(*lt)->brightness = ft_atodbl(lst[i]);
	}
	if ((i == 1 && c == 2) || (i == 2 && !fl))
	{
		(*lt)->color = malloc(sizeof(t_vctr));
		(*lt)->color->x = 255.0;
		(*lt)->color->y = 255.0;
		(*lt)->color->z = 255.0;
	}
	else if (i == 2)
		ft_assign_light_color(lt, lst[i]);
}

void	ft_assign_alight_color(t_alight **lt, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("Ambiant light color has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("Ambiant light color incorrect", 1);
	(*lt)->color = malloc(sizeof(t_vctr));
	(*lt)->color->x = ft_atodbl(tmp[0]);
	(*lt)->color->y = ft_atodbl(tmp[1]);
	(*lt)->color->z = ft_atodbl(tmp[2]);
	if (((*lt)->color->x > 255 || (*lt)->color->y > 255
			|| (*lt)->color->z > 255) || ((*lt)->color->x < 0
			|| (*lt)->color->y < 0 || (*lt)->color->z < 0))
		ft_print_and_exit("Ambiant light has wrong color parameters", 1);
	ft_lstfree(tmp);
}
