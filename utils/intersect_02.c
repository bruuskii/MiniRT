/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:11:55 by izouine           #+#    #+#             */
/*   Updated: 2025/02/25 14:25:51 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_get_plane_axes(t_vctr *plane_u, t_vctr *plane_v, t_vctr *normal)
{
	t_vctr	up;
	double	dot;

	up = (t_vctr){0, 1, 0};
	dot = vec3_dot(*normal, up);
	if (fabs(dot) > 1e-6)
		up = (t_vctr){0, 0, 1};
	*plane_u = vec3_normalize(vec3_cross(*normal, up));
	*plane_v = vec3_normalize(vec3_cross(*normal, *plane_u));
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
	if (fabs(u) > M_W || (fabs(v) > M_H))
		return (1);
	return (0);
}

t_vctr	ft_calculate_intersection_plane(t_vctr denom, t_plane *plane, double t,
		t_ray *ray)
{
	t_vctr	inter;
	
	(void)plane;
	inter = vec3_add(*ray->origin, vec3_scale(denom, t));
	return (inter);
}

void	ft_assign_hit_plane(t_hit *hit, t_ray *ray, t_plane *plane, double t)
{
	double	den;
	t_vctr	ray_norm;

	ray_norm = vec3_normalize(*ray->direction);
	den = vec3_dot(ray_norm, *plane->normal);
	hit->hit = 1;
	hit->t = t;
	hit->point = ft_calculate_intersection_plane(ray_norm, plane, hit->t, ray);
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
	if (is_zero_vector(ft_calculate_intersection_plane(ray_norm, plane, t,
				ray)))
		return (free(hit->mtrl), free(hit), NULL);
	ft_assign_hit_plane(hit, ray, plane, t);
	return (hit);
}
