/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 11:41:10 by kbassim           #+#    #+#             */
/*   Updated: 2025/03/02 17:01:20 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_hit	*ft_innit_hit(t_ray *ray, t_world *tp)
{
	t_hit	*hit;

	hit = NULL;
	if (tp->type == 0)
		ft_innit_hit_sp(ray, tp, &hit);
	else if (tp->type == 1)
		ft_innit_hit_pl(ray, tp, &hit);
	else if (tp->type == 2)
		ft_innit_hit_cy(ray, tp, &hit);
	else if (tp->type == 5)
		ft_innit_hit_cn(ray, tp, &hit);
	return (hit);
}

void	ft_free_hit_elems(t_hit *hit)
{
	free(hit->mtrl);
	free(hit);
}

void	ft_free_scene_utils(t_hit *hit, t_ray *ray)
{
	free(ray->direction);
	free(ray);
	if (hit)
	{
		free(hit->mtrl);
		free(hit);
	}
}

void	ft_get_hit_color(t_world *world, t_hit *hit)
{
	t_sp		*sp;
	t_cone		*cone;
	t_plane		*plane;
	t_cylinder	*cy;

	if (hit->type == SPHERE)
	{
		sp = (t_sp *)world->ptr;
		ft_check_txtr(sp->texture, &hit->mtrl->color, sp->color);
	}
	else if (hit->type == PLANE)
	{
		plane = (t_plane *)world->ptr;
		ft_check_txtr(plane->texture, &hit->mtrl->color, plane->color);
	}
	else if (hit->type == CYLINDRE)
	{
		cy = (t_cylinder *)world->ptr;
		ft_check_txtr(cy->texture, &hit->mtrl->color, cy->color);
	}
	else if (hit->type == CONE)
	{
		cone = (t_cone *)world->ptr;
		ft_check_txtr(cone->texture, &hit->mtrl->color, cone->color);
	}
}

t_hit	*ft_get_hit(t_ray *ray, t_world *world)
{
	t_hit	*hit;
	t_hit	*c_hit;
	t_world	*tp;

	hit = NULL;
	c_hit = NULL;
	tp = world;
	while (tp)
	{
		hit = ft_innit_hit(ray, tp);
		if (hit && hit->hit)
		{
			ft_get_hit_color(tp, hit);
			if (!c_hit || hit->t < c_hit->t)
			{
				if (c_hit)
					ft_free_hit_elems(c_hit);
				c_hit = hit;
			}
			else
				ft_free_hit_elems(hit);
		}
		tp = tp->next;
	}
	return (c_hit);
}
