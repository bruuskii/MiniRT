/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:37:37 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/01 22:15:46 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_fl_sp(t_world *tp)
{
	t_sp	*sp;

	sp = tp->ptr;
	if (sp->texture)
		tp->fl = 1;
}

void	ft_assign_fl_pl(t_world *tp)
{
	t_plane	*pl;

	pl = tp->ptr;
	if (pl->texture)
		tp->fl = 1;
}

void	ft_assign_fl_cy(t_world *tp)
{
	t_cylinder	*cy;

	cy = tp->ptr;
	if (cy->texture)
		tp->fl = 1;
}

void	ft_assign_fl_cn(t_world *tp)
{
	t_cone	*cn;

	cn = tp->ptr;
	if (cn->texture)
		tp->fl = 1;
}

void	ft_assign_fl(t_world *world)
{
	t_world	*tp;

	tp = world;
	while (tp)
	{
		if (tp->type == 0)
			ft_assign_fl_sp(tp);
		else if (tp->type == 1)
			ft_assign_fl_pl(tp);
		else if (tp->type == 2)
			ft_assign_fl_cy(tp);
		else if (tp->type == 5)
			ft_assign_fl_cn(tp);
		tp = tp->next;
	}
}
