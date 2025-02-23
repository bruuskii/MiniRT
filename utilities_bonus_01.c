/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_bonus_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:36:13 by kbassim           #+#    #+#             */
/*   Updated: 2025/02/23 11:36:33 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_assign_txtr_sp(t_world *tp)
{
	t_sp	*sp;

	sp = (t_sp *)tp->ptr;
	if (sp->texture)
	{
		tp->txtr_ref = ft_strdup(sp->txtr_ref);
		free(sp->txtr_ref);
	}
}

void	ft_assign_txtr_pl(t_world *tp)
{
	t_plane	*pl;

	pl = (t_plane *)tp->ptr;
	if (pl->texture)
	{
		tp->txtr_ref = ft_strdup(pl->txtr_ref);
		free(pl->txtr_ref);
	}
}

void	ft_assign_txtr_cy(t_world *tp)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)tp->ptr;
	if (cy->texture)
	{
		tp->txtr_ref = ft_strdup(cy->txtr_ref);
		free(cy->txtr_ref);
	}
}

void	ft_assign_txtr_cn(t_world *tp)
{
	t_cone	*cn;

	cn = (t_cone *)tp->ptr;
	if (cn->texture)
	{
		tp->txtr_ref = ft_strdup(cn->txtr_ref);
		free(cn->txtr_ref);
	}
}

void	ft_assign_txtrs(t_world **world)
{
	t_world	*tp;

	tp = *world;
	while (tp)
	{
		if (tp->type == 0)
			ft_assign_txtr_sp(tp);
		else if (tp->type == 1)
			ft_assign_txtr_pl(tp);
		else if (tp->type == 2)
			ft_assign_txtr_cy(tp);
		else if (tp->type == 5)
			ft_assign_txtr_cy(tp);
		tp = tp->next;
	}
}
