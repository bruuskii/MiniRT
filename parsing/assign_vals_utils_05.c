/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils_05.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:32:55 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/04 17:46:33 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_alight_utils(t_alight **lt, char **lst, int i)
{
	if (i == 0)
	{
		if (is_valid_str(lst[i]))
			ft_print_and_exit("Light direction has non numerical", 1);
		(*lt)->ratio = ft_atodbl(lst[i]);
		if ((*lt)->ratio < 0)
			ft_print_and_exit("Ambiant light ratio should be positive\n", 1);
	}
	else if (i == 1)
		ft_assign_alight_color(lt, lst[i]);
}

void	ft_assign_cn_vertex(t_cone **cn, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
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

void	ft_assign_cn_color(t_cone **cn, char *s)
{
	char	**tmp;
	int		n;

	tmp = ft_split(s, ',');
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

void	ft_assign_cn_axis(t_cone **cn, char *lst)
{
	char	**tmp;
	int		n;

	tmp = ft_split(lst, ',');
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
	if ((*cn)->axis->x < -1 || (*cn)->axis->x > 1)
		ft_print_and_exit("Error: cone axis x out of range [-1, 1]", 1);
	if ((*cn)->axis->y < -1 || (*cn)->axis->y > 1)
		ft_print_and_exit("Error: cone axis y out of range [-1, 1]", 1);
	if ((*cn)->axis->z < -1 || (*cn)->axis->z > 1)
		ft_print_and_exit("Error: cone axis z out of range [-1, 1]", 1);
	ft_lstfree(tmp);
}

void	ft_assign_cn_tang(t_cone **cn, char *s)
{
	if (is_valid_str(s))
		ft_print_and_exit("Cone tangent has non numerical", 1);
	(*cn)->tang = ft_atodbl(s);
}
