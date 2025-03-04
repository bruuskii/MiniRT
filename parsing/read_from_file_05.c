/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_05.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:24:13 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/04 19:40:51 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_flag_cn(int n, char **tmp, t_cone *node, int fl)
{
	if (n == 8 && fl)
	{
		if (!ft_strcmp(tmp[6], "T") && tmp[7])
		{
			node->texture = 1;
			node->txtr_ref = ft_strdup(tmp[7]);
			if (ft_check_txtr_extention(node->txtr_ref))
				return ;
		}
		else
			ft_print_and_exit("Wrong parameters", 1);
	}
}

void	ft_assign_cone_ptr(char **tmp, t_cone **lt, int fl)
{
	t_cone	*ptr;
	t_cone	*node;
	int		n;

	n = ft_lst_count(tmp);
	if (n < 7 || n > 8)
		ft_print_and_exit("Cone has wrong number of elements", 1);
	ptr = malloc(sizeof(t_cone));
	if (!ptr)
		return ;
	ft_assign_cone(ptr, tmp + 1, n);
	node = ft_new_cone(ptr);
	ft_assign_flag_cn(n, tmp, node, fl);
	ft_add_back_cn(lt, node);
	free(ptr);
}

t_cone	*ft_cone(char **lst, int fl)
{
	int		i;
	char	**tmp;
	t_cone	*lt;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	lt = NULL;
	while (lst[i])
	{
		tmp = ft_fullsplit(lst[i]);
		if (!ft_check_first_param(tmp[0]))
			ft_print_and_exit("Unditenfied object", 1);
		if (!ft_strcmp(tmp[0], "cn"))
			ft_assign_cone_ptr(tmp, &lt, fl);
		ft_lstfree(tmp);
		i++;
	}
	return (lt);
}
