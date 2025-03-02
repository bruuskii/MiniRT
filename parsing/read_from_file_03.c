/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_03.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:27:59 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 15:17:56 by kbassim          ###   ########.fr       */
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
		node->texture = 1;
		node->txtr_ref = ft_strdup(tmp[4]);
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
	if (((n < 4 || n > 5) && fl) || (n != 4 && !fl))
		ft_print_and_exit("Plane has wrong number of elements", 1);
	ptr = malloc(sizeof(t_plane));
	if (!ptr)
		return ;
	ft_assign_plane(ptr, tmp + 1, n);
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
