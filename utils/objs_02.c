/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:23:59 by izouine           #+#    #+#             */
/*   Updated: 2025/03/01 22:22:34 by kbassim          ###   ########.fr       */
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

void	fill_color(t_helpers h)
{
	h.color.x = fmin(fmax(h.color.x, 0.0), 255.0);
	h.color.y = fmin(fmax(h.color.y, 0.0), 255.0);
	h.color.z = fmin(fmax(h.color.z, 0.0), 255.0);
}
