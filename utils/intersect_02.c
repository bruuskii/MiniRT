/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:11:55 by izouine           #+#    #+#             */
/*   Updated: 2025/03/01 14:22:51 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"


t_hit	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit	*hit;
	t_vctr	D;
	double	denom;
	t_vctr	N;
	t_vctr	ray_to_plane;
	t_vctr  intersection;
	double	t;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
    hit->t = INFINITY;
    D = vec3_normalize(*ray->direction);
    N = vec3_normalize(*plane->normal);
    denom = vec3_dot(D, N);
    const double EPSILON = 1e-5;
    if (fabs(denom) < EPSILON)
        return (free(hit->mtrl), free(hit), NULL);
    ray_to_plane = vec3_sub(*plane->point, *ray->origin);
    t = vec3_dot(ray_to_plane, N) / denom;
    if (t < EPSILON)
        return (free(hit->mtrl), free(hit), NULL);
    intersection = vec3_add(*ray->origin, vec3_scale(D, t));
    hit->hit = 1;
    hit->t = t;
    hit->point = intersection;
    if (denom < 0)
        hit->normal = N;
    else
        hit->normal = vec3_scale(N, -1);
    return hit;
}
