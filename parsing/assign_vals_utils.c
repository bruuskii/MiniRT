/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:37:17 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/14 02:05:11 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	is_valid_str(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
			return (1);
		else if (s[i] == '.')
			c++;
		i++;
	}
	return (c > 1);
}

int	valid_syntax(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		if (is_valid_str(lst[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_assign_plane_utils(t_plane **pl, char **lst, int i)
{
	char	**tmp;
	int		n;

	if (!*pl || !pl)
		return ;
	if (i == 0)
	{
		tmp = ft_split(lst[i], ',');
		if (!tmp)
			return ;
		if (valid_syntax(tmp))
			ft_print_and_exit("plane point has non numerical", 1);
		n = ft_lst_count(tmp);
		if (n != 3)
			ft_print_and_exit("plane point incorrect", 1);
		(*pl)->point = malloc(sizeof(t_vctr));
		if (!(*pl)->point)
			return ;
		(*pl)->point->x = ft_atodbl(tmp[0]);
		(*pl)->point->y = ft_atodbl(tmp[1]);
		(*pl)->point->z = ft_atodbl(tmp[2]);
		ft_lstfree(tmp);
	}
	else if (i == 1)
	{
		tmp = ft_split(lst[i], ',');
		if (!tmp)
			return ;
		if (valid_syntax(tmp))
			ft_print_and_exit("plane normal has non numerical", 1);
		(*pl)->normal = malloc(sizeof(t_vctr));
		n = ft_lst_count(tmp);
		if (n != 3)
			ft_print_and_exit("plane normal incorrect", 1);
		if (!(*pl)->point)
			return ;
		(*pl)->normal->x = ft_atodbl(tmp[0]);
		(*pl)->normal->y = ft_atodbl(tmp[1]);
		(*pl)->normal->z = ft_atodbl(tmp[2]);
		ft_lstfree(tmp);
	}
	else if (i == 2)
	{
		tmp = ft_split(lst[i], ',');
		if (!tmp)
			return ;
		if (valid_syntax(tmp))
			ft_print_and_exit("plane color has non numerical", 1);
		(*pl)->color = malloc(sizeof(t_vctr));
		n = ft_lst_count(tmp);
		if (n != 3)
			ft_print_and_exit("plane color incorrect", 1);
		if (!(*pl)->color)
			return ;
		(*pl)->color->x = ft_atodbl(tmp[0]);
		(*pl)->color->y = ft_atodbl(tmp[1]);
		(*pl)->color->z = ft_atodbl(tmp[2]);
		if (((*pl)->color->x > 255 || (*pl)->color->y > 255
				|| (*pl)->color->z > 255) || ((*pl)->color->x < 0
				|| (*pl)->color->y < 0 || (*pl)->color->z < 0))
			ft_print_and_exit("Plane has wrong color parameters", 1);
		ft_lstfree(tmp);
	}
}

void	ft_assign_cy_utils(t_cylinder **cy, char **lst, int i)
{
	char	**tmp;
	int		n;

	if (!*cy || !cy)
		return ;
	if (i == 0)
	{
		tmp = ft_split(lst[i], ',');
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
	else if (i == 1)
	{
		tmp = ft_split(lst[i], ',');
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
	{
		tmp = ft_split(lst[i], ',');
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
}

void	ft_assign_sp_utils(t_sp **sp, char **lst, int i)
{
	char	**tmp;
	int		n;

	if (!*sp || !sp)
		return ;
	tmp = NULL;
	if (i == 0)
	{
		tmp = ft_split(lst[i], ',');
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
	else if (i == 1)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("sphere diameter has non numerical", 1);
		(*sp)->d = ft_atodbl(lst[1]);
	}
	else if (i == 2)
	{
		tmp = ft_split(lst[i], ',');
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
}

void	ft_assign_cam_utils(t_cam **cam, char **lst, int i)
{
	char	**tmp;
	int		n;

	tmp = NULL;
	if (i == 1)
	{
		tmp = ft_split(lst[i], ',');
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
	else if (i == 2)
	{
		tmp = ft_split(lst[i], ',');
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
	else if (i == 3)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Field of view has non numerical", 1);
		(*cam)->fov = ft_atodbl(lst[i]);
		if ((*cam)->fov > 360)
			ft_print_and_exit("Field of view overflow", 1);
	}
}

void	ft_assign_light_utils(t_light **lt, char **lst, int i)
{
	char	**tmp;
	int		n;

	tmp = NULL;
	if (i == 0)
	{
		tmp = ft_split(lst[i], ',');
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
	else if (i == 1)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Light brightness has non numerical", 1);
		(*lt)->brightness = ft_atodbl(lst[i]);
	}
	else if (i == 2)
	{
		tmp = ft_split(lst[i], ',');
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
}

void	ft_assign_alight_utils(t_alight **lt, char **lst, int i)
{
	char	**tmp;
	int		n;

	tmp = NULL;
	if (i == 0)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Light direction has non numerical", 1);
		(*lt)->ratio = ft_atodbl(lst[i]);
		if ((*lt)->ratio < 0)
			ft_print_and_exit("Ambiant light ratio should be positive\n", 1);
	}
	else if (i == 1)
	{
		tmp = ft_split(lst[i], ',');
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
}

void	ft_assign_cn_utils(t_cone **cn, char **lst, int i)
{
	char **tmp;
	int n;

	if (!*cn || !cn)
		return ;
	if (i == 0)
	{
		tmp = ft_split(lst[i], ',');
		if (!tmp)
			return ;
		if (valid_syntax(tmp))
			ft_print_and_exit("Cone vertex has non numerical", 1);
		n = ft_lst_count(tmp);
		if (n != 3)
			ft_print_and_exit("Incorrct cone vertex", 1);
		(*cn)->vertex = malloc(sizeof(t_vctr));
		(*cn)->vertex->x = ft_atodbl(tmp[0]);
		(*cn)->vertex->y = ft_atodbl(tmp[1]);
		(*cn)->vertex->z = ft_atodbl(tmp[2]);
		ft_lstfree(tmp);
	}
	else if (i == 1)
	{
		tmp = ft_split(lst[i], ',');
		if (!tmp)
			return ;
		if (valid_syntax(tmp))
			ft_print_and_exit("Cone axis has non numerical", 1);
		n = ft_lst_count(tmp);
		if (n != 3)
			ft_print_and_exit("Incorrct cone axis", 1);
		(*cn)->axis = malloc(sizeof(t_vctr));
		(*cn)->axis->x = ft_atodbl(tmp[0]);
		(*cn)->axis->y = ft_atodbl(tmp[1]);
		(*cn)->axis->z = ft_atodbl(tmp[2]);
		ft_lstfree(tmp);
	}
	else if (i == 2)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Cone tangent has non numerical", 1);
		(*cn)->tang = ft_atodbl(lst[i]);
	}
	else if (i == 3)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Cone minm has non numerical", 1);
		(*cn)->minm = ft_atodbl(lst[i]);
	}
	else if (i == 4)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Cone maxm has non numerical", 1);
		(*cn)->maxm = ft_atodbl(lst[i]);
	}
	else if (i == 5)
	{
		tmp = ft_split(lst[i], ',');
		if (!tmp)
			return ;
		if (valid_syntax(tmp))
			ft_print_and_exit("Cone color has non numerical", 1);
		n = ft_lst_count(tmp);
		if (n != 3)
			ft_print_and_exit("Incorrct cone axis", 1);
		(*cn)->color = malloc(sizeof(t_vctr));
		(*cn)->color->x = ft_atodbl(tmp[0]);
		(*cn)->color->y = ft_atodbl(tmp[1]);
		(*cn)->color->z = ft_atodbl(tmp[2]);
		if (((*cn)->color->x > 255 || (*cn)->color->y > 255
				|| (*cn)->color->z > 255) || ((*cn)->color->x < 0
				|| (*cn)->color->y < 0 || (*cn)->color->z < 0))
			ft_print_and_exit("Cone has wrong color parameters", 1);
		ft_lstfree(tmp);
	}
}
