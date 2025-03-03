/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:20:06 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/03 00:36:31 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_planes(t_plane *pl, t_light *light)
{
	if (!pl || !light || !pl->normal || !pl->point || !light->dir)
		return (0);
	if (pl->normal->x && light->dir->x > 0 && pl->point->x > 0)
		if (light->dir->x > pl->point->x)
			return (0);
	if (pl->normal->x && light->dir->x < 0 && pl->point->x < 0)
		if (light->dir->x < pl->point->x)
			return (0);
	if (pl->normal->y && light->dir->y > 0 && pl->point->y > 0)
		if (light->dir->y > pl->point->y)
			return (0);
	if (pl->normal->y && light->dir->y < 0 && pl->point->y < 0)
		if (light->dir->y < pl->point->y)
			return (0);
	if (pl->normal->z && light->dir->z > 0 && pl->point->z > 0)
		if (light->dir->z > pl->point->z)
			return (0);
	if (pl->normal->z && light->dir->z < 0 && pl->point->z < 0)
		if (light->dir->z < pl->point->z)
			return (0);
	return (1);
}

int	get_fl(t_world *world, t_light *light)
{
	t_world	*current_wrld;
	t_plane	*pl;
	int		fl;

	current_wrld = world;
	fl = 0;
	while (current_wrld)
	{
		if (current_wrld->type == PLANE)
		{
			pl = (t_plane *)current_wrld->ptr;
			fl = check_planes(pl, light);
			if (pl && pl->normal && pl->point)
			{
				if (!fl)
					break ;
			}
		}
		current_wrld = current_wrld->next;
	}
	return (fl);
}
