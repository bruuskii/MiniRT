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

void	ft_assign_ptr_plane(char **tmp, t_plane **lt)
{
	t_plane	*ptr;
	t_plane	*node;

	if (ft_lst_count(tmp) != 4)
		ft_print_and_exit("Plane has wrong number of elements", 1);
	ptr = malloc(sizeof(t_plane));
	if (!ptr)
		return ;
	ft_assign_plane(ptr, tmp + 1);
	node = ft_new_pl(ptr);
	ft_add_back_pl(lt, node);
	free(ptr);
}

t_plane	*ft_obj_pl(char **lst, int fl)
{
	int		i;
	char	**tmp;
	t_plane	*lt;

	(void)fl;
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
			ft_assign_ptr_plane(tmp, &lt);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}

void	ft_assign_cy_ptr(char **tmp, t_cylinder **lt)
{
	t_cylinder	*ptr;
	t_cylinder	*node;

	if (ft_lst_count(tmp) != 6)
		ft_print_and_exit("Cylinder has wrong number of elements", 1);
	ptr = malloc(sizeof(t_cylinder));
	if (!ptr)
		return ;
	ft_assign_cy(ptr, tmp + 1);
	node = ft_new_cy(ptr);
	ft_add_back_cy(lt, node);
	free(ptr);
}

t_cylinder	*ft_obj_cy(char **lst)
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
			ft_assign_cy_ptr(tmp, &lt);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}
