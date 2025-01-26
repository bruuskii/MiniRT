/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:11:55 by izouine           #+#    #+#             */
/*   Updated: 2025/01/25 15:22:32 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_get_plane_axes(t_vctr *plane_u, t_vctr *plane_v, t_vctr *normal)
{
	t_vctr	up;

	if (fabs(normal->z) > 0.9)
	{
		*plane_u = (t_vctr){1, 0, 0};
		*plane_v = (t_vctr){0, 1, 0};
	}
	else
	{
		if (fabs(normal->y) < 0.9)
			up = (t_vctr){0, 1, 0};
		else
			up = (t_vctr){0, 0, 1};
		*plane_u = vec3_normalize(vec3_cross(*normal, up));
		*plane_v = vec3_normalize(vec3_cross(*normal, *plane_u));
	}
}

int	ft_resize_plane_00(t_vctr intersection, t_plane *plane)
{
	t_vctr	plane_u;
	t_vctr	plane_v;
	double	u;
	double	v;
	t_vctr	local_point;

	ft_get_plane_axes(&plane_u, &plane_v, plane->normal);
	local_point = vec3_sub(intersection, *plane->point);
	u = vec3_dot(local_point, plane_u);
	v = vec3_dot(local_point, plane_v);
	if (fabs(u) > M_W / 2 || (fabs(v) >= M_H / 2))
		return (1);
	return (0);
}

t_vctr	ft_calculate_intersection_plane(t_vctr denom, t_plane *plane, double t,
		t_ray *ray)
{
	t_vctr	intersection;

	intersection = vec3_add(ray->origin, vec3_scale(denom, t));
	if (!plane->normal->z)
		if (ft_resize_plane_00(intersection, plane))
			return ((t_vctr){0, 0, 0});
	return (intersection);
}

void	ft_assign_hit_plane(t_hit *hit, t_ray *ray, t_plane *plane, double t)
{
	double	den;
	t_vctr	denom;

	denom = vec3_normalize(ray->direction);
	den = vec3_dot(denom, *plane->normal);
	hit->hit = 1;
	hit->t = t;
	hit->point = ft_calculate_intersection_plane(denom, plane, hit->t, ray);
	if (den < 0)
		hit->normal = *plane->normal;
	else
		hit->normal = vec3_scale(*plane->normal, -1);
}

t_hit	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_hit	*hit;
	t_vctr	denom;
	double	den;
	t_vctr	ray_to_plane;
	double	t;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	hit->hit = 0;
	hit->t = 0;
	denom = vec3_normalize(ray->direction);
	den = vec3_dot(denom, *plane->normal);
	if (fabs(den) < 1e-6)
		return (hit);
	ray_to_plane = vec3_sub(*plane->point, ray->origin);
	t = vec3_dot(ray_to_plane, *plane->normal) / den;
	if (t < 1e-6)
		return (hit);
	if (is_zero_vector(ft_calculate_intersection_plane(denom, plane, t, ray)))
		return (hit);
	ft_assign_hit_plane(hit, ray, plane, t);
	return (hit);
}
