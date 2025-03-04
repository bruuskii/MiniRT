/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_04.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:27:57 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/04 19:27:57 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_process_cam(char *s, t_cam **ptr, int *c)
{
	char	**tmp;
	int		n;

	tmp = ft_fullsplit(s);
	if (!tmp)
		ft_print_and_exit("Split failed", 1);
	if (!ft_check_first_param(tmp[0]))
		ft_print_and_exit("Undefined object", 1);
	if (tmp[0] && !ft_strcmp(tmp[0], "C"))
	{
		n = ft_lst_count(tmp);
		if (n != 4)
			ft_print_and_exit("The camera has incorrect parameters", 1);
		if (*c > 1)
			ft_print_and_exit("Only one camera is needed", 1);
		(*c)++;
		*ptr = malloc(sizeof(t_cam));
		if (!*ptr)
			ft_print_and_exit("Memory allocation failed", 1);
		ft_assign_camera(*ptr, tmp);
	}
	ft_lstfree(tmp);
}

t_cam	*ft_cam(char **lst)
{
	int		i;
	t_cam	*ptr;
	int		c;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	c = 0;
	ptr = NULL;
	while (lst[i])
	{
		ft_process_cam(lst[i], &ptr, &c);
		i++;
	}
	if (!c)
		ft_print_and_exit("A camera is needed", 1);
	return (ptr);
}

void	ft_process_light(char *s, t_light **lt, int *c, int fl)
{
	char	**tmp;
	t_light	*node;
	int		count;

	tmp = ft_fullsplit(s);
	if (!tmp)
		ft_print_and_exit("Split failed", 1);
	count = ft_lst_count(tmp);
	if (!ft_check_first_param(tmp[0]))
		ft_print_and_exit("Undefined object", 1);
	if (!ft_strcmp(tmp[0], "L"))
	{
		if ((count != 4 && fl) || (!fl && (count < 3 || count > 4)))
			ft_print_and_exit("Light has wrong number of elements", 1);
		node = ft_new_lt();
		ft_assign_light(node, tmp + 1, fl);
		ft_add_back_lt(lt, node);
		(*c)++;
	}
	ft_lstfree(tmp);
}

t_light	*ft_light(char **lst, int fl)
{
	int		i;
	t_light	*lt;
	int		c;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	c = 0;
	lt = NULL;
	while (lst[i])
	{
		ft_process_light(lst[i], &lt, &c, fl);
		i++;
	}
	return (lt);
}

void	ft_alight_ptr(int *c, char **tmp, t_alight **node)
{
	t_alight	*new_node;

	if (!tmp || ft_lst_count(tmp) != 3)
		ft_print_and_exit("Ambient light has wrong number of elements", 1);
	new_node = malloc(sizeof(t_alight));
	if (!new_node)
		ft_print_and_exit("Memory allocation failed", 1);
	ft_assign_alight(new_node, tmp + 1);
	if (*c > 1)
		ft_print_and_exit("Only one ambient light is needed", 1);
	*node = new_node;
	(*c)++;
}
