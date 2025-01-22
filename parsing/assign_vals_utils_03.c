/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils_03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:33:01 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:38:52 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_sp_center(t_sp **sp, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("Sphere center has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("Sphere center incorrect", 1);
	(*sp)->cntr = malloc(sizeof(t_vctr));
	(*sp)->cntr->x = ft_atodbl(tmp[0]);
	(*sp)->cntr->y = ft_atodbl(tmp[1]);
	(*sp)->cntr->z = ft_atodbl(tmp[2]);
	ft_lstfree(tmp);
}

void	ft_assign_sp_utils_color(t_sp **sp, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("sphepre color has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("sphere color incorrect", 1);
	(*sp)->color = malloc(sizeof(t_vctr));
	(*sp)->color->x = ft_atodbl(tmp[0]);
	(*sp)->color->y = ft_atodbl(tmp[1]);
	(*sp)->color->z = ft_atodbl(tmp[2]);
	if (((*sp)->color->x > 255 || (*sp)->color->y > 255
			|| (*sp)->color->z > 255) || ((*sp)->color->x < 0
			|| (*sp)->color->y < 0 || (*sp)->color->z < 0))
		ft_print_and_exit("Sphere has wrong color parameters", 1);
	ft_lstfree(tmp);
}

void	ft_assign_sp_utils(t_sp **sp, char **lst, int i)
{
	if (!*sp || !sp)
		return ;
	if (i == 0)
		ft_assign_sp_center(sp, lst[i]);
	else if (i == 1)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("sphere diameter has non numerical", 1);
		(*sp)->d = ft_atodbl(lst[1]);
	}
	else if (i == 2)
		ft_assign_sp_utils_color(sp, lst[i]);
}

void	ft_assign_cam_utils_pos(t_cam **cam, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("camera position has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("camera position incorrect", 1);
	(*cam)->pos = malloc(sizeof(t_vctr));
	(*cam)->pos->x = ft_atodbl(tmp[0]);
	(*cam)->pos->y = ft_atodbl(tmp[1]);
	(*cam)->pos->z = ft_atodbl(tmp[2]);
	ft_lstfree(tmp);
}

void	ft_assign_cam_utils_dir(t_cam **cam, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("camera direction has non numerical", 1);
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("camera direction incorrect", 1);
	(*cam)->dir = malloc(sizeof(t_vctr));
	(*cam)->dir->x = ft_atodbl(tmp[0]);
	(*cam)->dir->y = ft_atodbl(tmp[1]);
	(*cam)->dir->z = ft_atodbl(tmp[2]);
	ft_lstfree(tmp);
}
