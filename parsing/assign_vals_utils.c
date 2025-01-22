/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:37:17 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/21 03:00:22 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_cn_utils(t_cone **cn, char **lst, int i)
{
	if (!*cn || !cn)
		return ;
	if (i == 0)
		ft_assign_cn_vertex(cn, lst[i]);
	else if (i == 1)
		ft_assign_cn_axis(cn, lst[i]);
	else if (i == 2)
		ft_assign_cn_tang(cn, lst[i]);
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
		ft_assign_cn_color(cn, lst[i]);
}
