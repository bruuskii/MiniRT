/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:33:07 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:33:08 by kbassim          ###   ########.fr       */
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

void	ft_assign_plane_point(t_plane **pl, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
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

void	ft_assign_plane_color(t_plane **pl, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
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

void	ft_assign_plane_normal(t_plane **pl, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
	if (!tmp)
		return ;
	if (valid_syntax(tmp))
		ft_print_and_exit("plane normal has non numerical", 1);
	(*pl)->normal = malloc(sizeof(t_vctr));
	n = ft_lst_count(tmp);
	if (n != 3)
		ft_print_and_exit("plane normal incorrect", 1);
	if (!(*pl)->normal)
		return ;
	(*pl)->normal->x = ft_atodbl(tmp[0]);
	(*pl)->normal->y = ft_atodbl(tmp[1]);
	(*pl)->normal->z = ft_atodbl(tmp[2]);
	if ((*pl)->normal->x < -1 || (*pl)->normal->x > 1)
		ft_print_and_exit("Error: Plane normal x out of range [-1, 1]", 1);
	if ((*pl)->normal->y < -1 || (*pl)->normal->y > 1)
		ft_print_and_exit("Error: Plane normal y out of range [-1, 1]", 1);
	if ((*pl)->normal->z < -1 || (*pl)->normal->z > 1)
		ft_print_and_exit("Error: Plane normal z out of range [-1, 1]", 1);
	ft_lstfree(tmp);
}
