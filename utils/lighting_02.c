/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:20:06 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/01 22:22:43 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_planes(t_plane *pl, t_light *light)
{
	int	fl;

	fl = 0;
	if (!pl || !light || !pl->normal || !pl->point || !light->dir)
		return (0);
	if (pl && pl->normal->x != 0)
	{
		if (light->dir->x > 0 && pl->point->x > 0
			&& light->dir->x > pl->point->x)
			fl = 1;
		if (light->dir->x < 0 && fabs(light->dir->x) > fabs(pl->point->x))
			fl = 1;
	}
	return (fl);
}

int	get_fl_utils(int inf, int *fl, t_plane *pl, t_light *light)
{
	t_vctr	sub;

	sub = vec3_sub(*light->dir, *pl->point);
	if (vec3_dot(sub, *pl->normal) < 0 && !inf)
	{
		*fl = 1;
		return (1);
	}
	else
		*fl = 0;
	return (0);
}

int	get_fl(t_world *world, t_light *light)
{
	t_world	*current_wrld;
	t_plane	*pl;
	int		fl;
	int		inf;

	current_wrld = world;
	fl = 0;
	inf = 0;
	while (current_wrld)
	{
		if (current_wrld->type == PLANE)
		{
			pl = (t_plane *)current_wrld->ptr;
			inf = check_planes(pl, light);
			if (pl && pl->normal && pl->point)
			{
				if (get_fl_utils(inf, &fl, pl, light))
					break ;
			}
		}
		current_wrld = current_wrld->next;
	}
	return (fl);
}
