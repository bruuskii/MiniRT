/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:42:28 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/20 01:58:56 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_alight	*ft_alight(char **lst)
{
	int			i;
	char		**tmp;
	int			c;
	t_alight	*node;

	if (!lst || !*lst)
		return (NULL);
	i = 0;
	c = 0;
	while (lst[i])
	{
		tmp = ft_fullsplit(lst[i]);
		if (!tmp)
			ft_print_and_exit("Split failed", 1);
		if (!ft_check_first_param(tmp[0]))
			ft_print_and_exit("Undefined object", 1);
		if (!ft_strcmp(tmp[0], "A"))
			ft_alight_ptr(&c, tmp, &node);
		ft_lstfree(tmp);
		i++;
	}
	if (c == 0)
		ft_print_and_exit("At least one ambient light is needed", 1);
	return (node);
}
