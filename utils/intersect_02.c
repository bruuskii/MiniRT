/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:11:55 by izouine           #+#    #+#             */
/*   Updated: 2025/02/28 00:28:20 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_assign_hit_plane(t_hit *hit, t_ray *ray, t_plane *plane, double t)
{
	double	den;
	t_vctr	ray_norm;

	ray_norm = vec3_normalize(*ray->direction);
	den = vec3_dot(ray_norm, *plane->normal);
	hit->hit = 1;
	hit->t = t;
	hit->point = vec3_add(*ray->origin, vec3_scale(vec3_normalize(*ray->direction), t));
	if (den < 0)
		hit->normal = *plane->normal;
	else
		hit->normal = vec3_scale(*plane->normal, -1);
}

t_hit	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit	*hit;
	t_vctr	ray_norm;
	double	den;
	t_vctr	ray_to_plane;
	double	t;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
	hit->t = 0;
	ray_norm = vec3_normalize(*ray->direction);
	den = vec3_dot(ray_norm, *plane->normal);
	if (fabs(den) < 1e-6)
		return (free(hit->mtrl), free(hit), NULL);
	ray_to_plane = vec3_sub(*plane->point, *ray->origin);
	t = vec3_dot(ray_to_plane, *plane->normal) / den;
	if (t < 1e-6)
		return (free(hit->mtrl), free(hit), NULL);
	ft_assign_hit_plane(hit, ray, plane, t);
	return (hit);
}
