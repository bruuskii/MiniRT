/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:27:59 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:35:19 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_sp	*ft_obj(char **lst, int fl)
{
	int		i;
	char	**tmp;
	t_sp	*lt;
	int		n;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	lt = NULL;
	while (lst[i])
	{
		tmp = ft_fullsplit(lst[i]);
		if (!ft_check_first_param(tmp[0]))
			ft_print_and_exit("Unditenfied object", 1);
		if (!ft_strcmp(tmp[0], "sp"))
		{
			n = ft_lst_count(tmp);
			ft_assign_sphere(tmp, &lt, n, fl);
		}
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

void	ft_assign_flag_plane(int n, char **tmp, t_plane *node, int fl)
{
	if (n == 5 && fl)
	{
		if (!ft_strcmp(tmp[4], "C"))
			ft_print_and_exit("Insufficient Parameters", 1);
	}
	else if (n == 6 && fl)
	{
		node->texture = 1;
		node->txtr_ref = ft_strdup(tmp[5]);
		if (ft_check_txtr_extention(node->txtr_ref))
			return ;
	}
}

void	ft_assign_ptr_plane(char **tmp, t_plane **lt, int fl)
{
	t_plane	*ptr;
	t_plane	*node;
	int		n;

	n = ft_lst_count(tmp);
	if (n < 4 || n > 6)
		ft_print_and_exit("Plane has wrong number of elements", 1);
	ptr = malloc(sizeof(t_plane));
	if (!ptr)
		return ;
	ft_assign_plane(ptr, tmp + 1);
	node = ft_new_pl(ptr);
	ft_assign_flag_plane(n, tmp, node, fl);
	ft_add_back_pl(lt, node);
	free(ptr);
}

t_plane	*ft_obj_pl(char **lst, int fl)
{
	int		i;
	char	**tmp;
	t_plane	*lt;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	lt = NULL;
	while (lst[i])
	{
		tmp = ft_fullsplit(lst[i]);
		if (!ft_check_first_param(tmp[0]))
			ft_print_and_exit("Unditenfied object", 1);
		if (!ft_strcmp(tmp[0], "pl"))
			ft_assign_ptr_plane(tmp, &lt, fl);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

void	ft_assign_flag_cy(int n, char **tmp, t_cylinder *node, int fl)
{
	if (n == 7 && fl)
	{
		if (!ft_strcmp(tmp[6], "C"))
			ft_print_and_exit("Insufficient Parameters", 1);
	}
	else if (n == 8 && fl)
	{
		node->texture = 1;
		node->txtr_ref = ft_strdup(tmp[7]);
		if (ft_check_txtr_extention(node->txtr_ref))
			exit (1);
	}
}

void	ft_assign_cy_ptr(char **tmp, t_cylinder **lt, int fl)
{
	t_cylinder	*ptr;
	t_cylinder	*node;
	int			n;

	n = ft_lst_count(tmp);
	if (n < 6 || n > 8)
		ft_print_and_exit("Cylinder has wrong number of elements", 1);
	ptr = malloc(sizeof(t_cylinder));
	if (!ptr)
		return ;
	ft_assign_cy(ptr, tmp + 1);
	node = ft_new_cy(ptr);
	ft_assign_flag_cy(n, tmp, node, fl);
	ft_add_back_cy(lt, node);
	free(ptr);
}

t_cylinder	*ft_obj_cy(char **lst, int fl)
{
	int			i;
	char		**tmp;
	t_cylinder	*lt;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	lt = NULL;
	while (lst[i])
	{
		tmp = ft_fullsplit(lst[i]);
		if (!tmp)
			return (NULL);
		if (!ft_check_first_param(tmp[0]))
			ft_print_and_exit("Unditenfied object", 1);
		if (!ft_strcmp(tmp[0], "cy"))
			ft_assign_cy_ptr(tmp, &lt, fl);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}
