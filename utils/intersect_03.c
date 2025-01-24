/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:11:58 by izouine           #+#    #+#             */
/*   Updated: 2025/01/24 17:44:47 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	ft_discriminant_cylinder(t_ray *ray, t_cylinder *cy, t_vctr oc)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction,
				*cy->c_axis), 2);
	b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction,
				*cy->c_axis) * vec3_dot(oc, *cy->c_axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, *cy->c_axis), 2) - pow(cy->d / 2,
			2);
	discriminant = b * b - 4 * a * c;
	return (discriminant);
}

int	ft_assign_t_cy(t_ray *ray, double *t, t_vctr oc, t_cylinder *cy)
{
	double	t1;
	double	t2;
	double	sqrt_discriminant;
	double	a;
	double	b;

	a = vec3_dot(ray->direction, ray->direction) - pow(vec3_dot(ray->direction,
				*cy->c_axis), 2);
	b = 2 * (vec3_dot(ray->direction, oc) - vec3_dot(ray->direction,
				*cy->c_axis) * vec3_dot(oc, *cy->c_axis));
	sqrt_discriminant = sqrt(ft_discriminant_cylinder(ray, cy, oc));
	t1 = (-b - sqrt_discriminant) / (2 * a);
	t2 = (-b + sqrt_discriminant) / (2 * a);
	*t = -1;
	if (t1 > 1e-6)
	{
		*t = t1;
		return (0);
	}
	else if (t2 > 1e-6)
	{
		*t = t2;
		return (0);
	}
	return (1);
}

double	ft_distance_cylinder(t_hit *hit, t_cylinder *cy)
{
	t_vctr	projection;
	t_vctr	proj_point;
	double	distance;

	distance = 0;
	projection = vec3_scale(*cy->c_axis, vec3_dot(vec3_sub(hit->point,
					*cy->c_cntr), *cy->c_axis));
	proj_point = vec3_add(*cy->c_cntr, projection);
	if (distance <= cy->height)
		hit->normal = vec3_normalize(vec3_sub(hit->point, proj_point));
	return (distance);
}

t_hit	*intersect_cylinder(t_ray *ray, t_cylinder *cy)
{
	t_hit	*hit;
	double	discriminant;
	double	t;
	t_vctr	oc;

	hit = ft_hit();
	if (!hit)
		return (NULL);
	oc = vec3_sub(ray->origin, *cy->c_cntr);
	hit->hit = 0;
	hit->t = 0;
	discriminant = ft_discriminant_cylinder(ray, cy, oc);
	if (discriminant < 0)
		return (hit);
	if (ft_assign_t_cy(ray, &t, oc, cy))
		return (hit);
	hit->t = t;
	hit->hit = 1;
	hit->point = vec3_add(ray->origin, vec3_scale(ray->direction, hit->t));
	if (ft_distance_cylinder(hit, cy) > cy->height)
		return (hit->hit = 0, hit);
	return (hit);
}

double	ft_calculate_k(double tang)
{
	return (tan(tang * M_PI / 180.0));
}
