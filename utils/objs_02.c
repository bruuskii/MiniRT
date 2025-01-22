/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:23:59 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:25:13 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_add_back_cn(t_cone **cn, t_cone *node)
{
	t_cone	*tmp;

	if (!*cn)
	{
		*cn = node;
		return ;
	}
	tmp = *cn;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
