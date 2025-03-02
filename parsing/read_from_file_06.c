/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_06.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:25:48 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 15:56:29 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_flag_cy(int n, char **tmp, t_cylinder *node, int fl)
{
	if (n == 7 && fl)
	{
		if (!ft_strcmp(tmp[5], "T") && tmp[6])
		{
			node->texture = 1;
			node->txtr_ref = ft_strdup(tmp[6]);
			if (ft_check_txtr_extention(node->txtr_ref))
				ft_print_and_exit("cone has wrong texture extention", 1);
		}
		else
			ft_print_and_exit("Insufficient Parameters", 1);
	}
}

void	ft_assign_cy_ptr(char **tmp, t_cylinder **lt, int fl)
{
	t_cylinder	*ptr;
	t_cylinder	*node;
	int			n;

	n = ft_lst_count(tmp);
	if (((n != 6) && !fl) || (fl && (n < 6 || n > 7)))
		ft_print_and_exit("Cylinder has wrong number of elements", 1);
	ptr = malloc(sizeof(t_cylinder));
	if (!ptr)
		return ;
	ft_assign_cy(ptr, tmp + 1, n);
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
