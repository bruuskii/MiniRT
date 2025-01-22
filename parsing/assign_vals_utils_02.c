/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:33:04 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:35:39 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_plane_utils(t_plane **pl, char **lst, int i)
{
	if (!*pl || !pl)
		return ;
	if (i == 0)
		ft_assign_plane_point(pl, lst[i]);
	else if (i == 1)
		ft_assign_plane_normal(pl, lst[i]);
	else if (i == 2)
		ft_assign_plane_color(pl, lst[i]);
}

void	ft_assign_cy_center(t_cylinder **cy, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("Cylinder center has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("Cylinder center incorrect", 1);
	(*cy)->c_cntr = malloc(sizeof(t_vctr));
	(*cy)->c_cntr->x = ft_atodbl(tmp[0]);
	(*cy)->c_cntr->y = ft_atodbl(tmp[1]);
	(*cy)->c_cntr->z = ft_atodbl(tmp[2]);
	ft_lstfree(tmp);
}

void	ft_assign_cy_axis(t_cylinder **cy, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("Cylinder axis has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("Cylinder axis incorrect", 1);
	(*cy)->c_axis = malloc(sizeof(t_vctr));
	(*cy)->c_axis->x = ft_atodbl(tmp[0]);
	(*cy)->c_axis->y = ft_atodbl(tmp[1]);
	(*cy)->c_axis->z = ft_atodbl(tmp[2]);
	ft_lstfree(tmp);
}

void	ft_assign_cy_utils_color(t_cylinder **cy, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("Cylinder color has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("Cylinder color incorrect", 1);
	(*cy)->color = malloc(sizeof(t_vctr));
	(*cy)->color->x = ft_atodbl(tmp[0]);
	(*cy)->color->y = ft_atodbl(tmp[1]);
	(*cy)->color->z = ft_atodbl(tmp[2]);
	if (((*cy)->color->x > 255 || (*cy)->color->y > 255
			|| (*cy)->color->z > 255) || ((*cy)->color->x < 0
			|| (*cy)->color->y < 0 || (*cy)->color->z < 0))
		ft_print_and_exit("Cylinder has wrong color parameters", 1);
	ft_lstfree(tmp);
}

void	ft_assign_cy_utils(t_cylinder **cy, char **lst, int i)
{
	if (!*cy || !cy)
		return ;
	if (i == 0)
		ft_assign_cy_center(cy, lst[i]);
	else if (i == 1)
		ft_assign_cy_axis(cy, lst[i]);
	else if (i == 2)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("cylinder diameter has non numerical", 1);
		(*cy)->d = ft_atodbl(lst[i]);
	}
	else if (i == 3)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("cylinder height has non numerical", 1);
		(*cy)->height = ft_atodbl(lst[i]);
	}
	else if (i == 4)
		ft_assign_cy_utils_color(cy, lst[i]);
}
