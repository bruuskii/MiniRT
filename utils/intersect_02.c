/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:11:55 by izouine           #+#    #+#             */
/*   Updated: 2025/03/01 22:12:24 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	utils_plane_intersection(double t, t_vctr n_plane, double denom,
		t_hit *hit)
{
	hit->hit = 1;
	hit->t = t;
	if (denom < 0)
		hit->normal = n_plane;
	else
		hit->normal = vec3_scale(n_plane, -1);
}

t_hit	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit		*hit;
	t_vctr		d_ray;
	t_helpers	h;
	t_vctr		n_plane;
	t_vctr		ray_to_plane;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
	hit->t = INFINITY;
	d_ray = vec3_normalize(*ray->direction);
	n_plane = vec3_normalize(*plane->normal);
	h.denom = vec3_dot(d_ray, n_plane);
	if (fabs(h.denom) < 1e-6)
		return (free(hit->mtrl), free(hit), NULL);
	ray_to_plane = vec3_sub(*plane->point, *ray->origin);
	h.t = vec3_dot(ray_to_plane, n_plane) / h.denom;
	if (h.t < 1e-6)
		return (free(hit->mtrl), free(hit), NULL);
	utils_plane_intersection(h.t, n_plane, h.denom, hit);
	hit->point = vec3_add(*ray->origin, vec3_scale(d_ray, h.t));
	return (hit);
}
