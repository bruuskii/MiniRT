/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_vals _01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:02:43 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:34:06 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_alight(t_alight *lt, char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		ft_assign_alight_utils(&lt, lst, i);
		i++;
	}
}

void	ft_assign_cone(t_cone *cn, char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		ft_assign_cn_utils(&cn, lst, i);
		i++;
	}
}
